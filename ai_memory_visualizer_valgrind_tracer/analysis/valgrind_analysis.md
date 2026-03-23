# Valgrind Analysis — AI Memory Tracer

> **Methodology**: Valgrind 3.22.0 was run with `--leak-check=full
> --track-origins=yes --show-leak-kinds=all -v` on each program.
> AI was used as a starting point to interpret output, then each
> explanation was verified against the source code and the memory maps
> from Task 1. All AI errors are documented explicitly.

---

## Table of Contents

1. [heap\_example](#1-heap_example)
2. [aliasing\_example](#2-aliasing_example)
3. [AI Error Documentation](#3-ai-error-documentation)

---

## 1. `heap_example`

### Valgrind command

```bash
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -v ./heap_example
```

### Raw output (relevant section)

```
==46744== HEAP SUMMARY:
==46744==     in use at exit: 6 bytes in 1 blocks
==46744==   total heap usage: 5 allocs, 4 frees, 1,066 bytes allocated
==46744==
==46744== 6 bytes in 1 blocks are definitely lost in loss record 1 of 1
==46744==    at 0x4885250: malloc (vgpreload_memcheck-arm64-linux.so)
==46744==    by 0x1088BF: person_new (heap_example.c:21)
==46744==    by 0x1089BB: main (heap_example.c:51)
==46744==
==46744== LEAK SUMMARY:
==46744==    definitely lost: 6 bytes in 1 blocks
==46744== ERROR SUMMARY: 1 errors from 1 contexts
```

---

### Issue 1 — Definite memory leak: `alice->name`

**Valgrind classification:** `definitely lost`

**Error type:** Memory leak — lost ownership

**Location:** `heap_example.c:21` (inside `person_new`), called from
`heap_example.c:51` (first call in `main`, which creates alice)

**Memory object involved:**
A `char` array of 6 bytes allocated by `malloc` inside `person_new`
to store the string `"Alice\0"`. At runtime its address was `0x4a7e4d0`.

**What "definitely lost" means:**
Valgrind uses this classification when no pointer in the program points
to the start of the block at exit. The block is permanently unreachable
and can never be freed — it is gone for the lifetime of the process.

**Causal chain:**

1. `person_new("Alice", 30)` calls `malloc(len + 1)` at line 21 to
   allocate the name buffer. The pointer is stored in `p->name` inside
   the `Person` struct.
2. The only pointer to this buffer is `alice->name` — it lives inside
   the `Person` struct on the heap.
3. `person_free_partial(alice)` is called at the end of `main`. Its
   implementation calls `free(p)`, which releases the `Person` struct.
4. At the moment `free(p)` executes, `p->name` (the only pointer to
   the name buffer) is inside the block being freed. After `free(p)`
   completes, that pointer is gone — no variable anywhere in the program
   holds the address `0x4a7e4d0`.
5. The name buffer is now unreachable. It will never be freed.

**Why bob does not leak:**
Bob is freed in two steps: `free(bob->name)` first (saving the pointer
before it is lost), then `free(bob)`. This is the correct order and
produces no leak.

**Heap state at exit:**

```
HEAP at program exit
┌──────────────────────────────────────┐
│ char[6] "Alice\0" @ 0x4a7e4d0       │  ← LEAKED (definitely lost)
│   No pointer references this block  │
└──────────────────────────────────────┘
```

**Allocation count confirmation:**
Valgrind reports 5 allocs and 4 frees.
- 5 allocs: alice struct + alice name + bob struct + bob name + 1 internal (stdio)
- 4 frees: alice struct (partial) + bob name + bob struct + 1 internal
- Net: 1 block unreleased = alice->name ✓

**Fix:**

```c
static void person_free_partial(Person *p)
{
    if (!p)
        return;
    free(p->name);   /* must free name BEFORE the struct */
    free(p);
}
```

---

## 2. `aliasing_example`

### Valgrind command

```bash
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -v ./aliasing_example
```

### Raw output (relevant section)

```
==47013== Invalid read of size 4
==47013==    at 0x108994: main (aliasing_example.c:42)
==47013==  Address 0x4a7e488 is 8 bytes inside a block of size 20 free'd
==47013==    at 0x48882A8: free (aliasing_example.c:38)
==47013==  Block was alloc'd at
==47013==    at 0x4885250: malloc
==47013==    by 0x10888B: make_numbers (aliasing_example.c:12)
==47013==    by 0x10891F: main (aliasing_example.c:30)

==47013== Invalid write of size 4
==47013==    at 0x1089B4: main (aliasing_example.c:44)
==47013==  Address 0x4a7e48c is 12 bytes inside a block of size 20 free'd

==47013== Invalid read of size 4
==47013==    at 0x1089C0: main (aliasing_example.c:45)
==47013==  Address 0x4a7e48c is 12 bytes inside a block of size 20 free'd

==47013== HEAP SUMMARY:
==47013==     in use at exit: 0 bytes in 0 blocks
==47013==   total heap usage: 2 allocs, 2 frees, 1,044 bytes allocated
==47013==
==47013== All heap blocks were freed -- no leaks are possible
==47013== ERROR SUMMARY: 3 errors from 3 contexts
```

---

### Issue 1 — Invalid read at `aliasing_example.c:42`

**Valgrind classification:** `Invalid read of size 4`

**Error type:** Use-after-free (read)

**Source line:**
```c
printf("  reading b[2]=%d\n", b[2]);   /* line 42 */
```

**Memory object involved:**
The `int[5]` array allocated by `make_numbers(5)` at address `0x4a7e480`,
size 20 bytes (5 × 4). The access is to `b[2]`, which is at offset
`2 * sizeof(int) = 8` bytes from the base — confirmed by Valgrind:
`Address 0x4a7e488 is 8 bytes inside a block of size 20 free'd`.

**Causal chain:**

1. `make_numbers(5)` allocates 20 bytes at `0x4a7e480` and returns
   the pointer. `a` receives it.
2. `b = a` creates an alias: both `a` and `b` hold `0x4a7e480`.
3. `free(a)` at line 38 releases the block. The allocator marks it as
   free and may write metadata into it.
4. `b` still holds `0x4a7e480` — it is now a dangling pointer.
5. `b[2]` reads 4 bytes at address `0x4a7e488`. This address belongs to
   a freed block. The read is invalid.

**Observed value:** `-872835351` (allocator metadata reinterpreted as
a signed `int`) — not the original `22`.

**Why it does not crash:**
The memory page is still mapped. The allocator keeps freed blocks in its
own internal free-list and does not immediately return the page to the OS.
The invalid read succeeds at the hardware level but produces undefined
results. Valgrind intercepts it because it tracks the allocation state
of every byte independently of the OS page table.

---

### Issue 2 — Invalid write at `aliasing_example.c:44`

**Valgrind classification:** `Invalid write of size 4`

**Error type:** Use-after-free (write) — heap corruption

**Source line:**
```c
b[3] = 1234;   /* line 44 */
```

**Memory object involved:**
Same freed block at `0x4a7e480`. The access is to `b[3]`, offset
`3 * sizeof(int) = 12` bytes — confirmed: `Address 0x4a7e48c is
12 bytes inside a block of size 20 free'd`.

**Causal chain:**

1. Same as Issue 1: the block was freed at line 38 via `free(a)`.
2. `b[3] = 1234` writes 4 bytes into the freed block.
3. This overwrites allocator metadata stored in the freed chunk.
4. If the allocator later attempts to coalesce this block with adjacent
   free blocks, or to hand it out for a new allocation, it will read
   corrupted metadata. This can cause crashes or silent data corruption
   at an arbitrary later point in the program.

**This is the most dangerous error in this program.** The invalid read
(Issue 1) is bad but passive. This write actively corrupts the heap
state and can cause failures that are difficult to trace back to their
origin.

---

### Issue 3 — Invalid read at `aliasing_example.c:45`

**Valgrind classification:** `Invalid read of size 4`

**Error type:** Use-after-free (read) — reading back the value just written

**Source line:**
```c
printf("  wrote b[3]=%d\n", b[3]);   /* line 45 */
```

**Memory object involved:**
Same freed block, same offset 12: `Address 0x4a7e48c is 12 bytes inside
a block of size 20 free'd`.

**Causal chain:**
This read immediately follows the write at line 44. The program writes
`1234` into the freed block, then reads it back to print it. Both
operations are on freed memory. The read happens to return `1234`
because nothing else modified that location between lines 44 and 45,
but this is coincidental and not guaranteed.

---

### Summary table — `aliasing_example`

| # | Type | Line | Address | Offset in block | Root cause |
|---|---|---|---|---|---|
| 1 | Invalid read (4 bytes) | 42 | 0x4a7e488 | +8 (b[2]) | Use-after-free read |
| 2 | Invalid write (4 bytes) | 44 | 0x4a7e48c | +12 (b[3]) | Use-after-free write |
| 3 | Invalid read (4 bytes) | 45 | 0x4a7e48c | +12 (b[3]) | Use-after-free read |

All three errors share the same root cause: `b` is an alias of `a`,
and `b` is used after `free(a)` without being set to NULL.

**No leak is reported** because `free(a)` is called and the allocator
accounts for the block. The problem is not a missing free — it is
accessing memory after freeing it.

---

### Address arithmetic verification

Block base: `0x4a7e480`, size: 20 bytes (5 × `int`).

| Index | Offset | Address | Valgrind reported |
|---|---|---|---|
| b[0] | +0 | 0x4a7e480 | — |
| b[1] | +4 | 0x4a7e484 | — |
| b[2] | +8 | 0x4a7e488 | ✓ "8 bytes inside" |
| b[3] | +12 | 0x4a7e48c | ✓ "12 bytes inside" |
| b[4] | +16 | 0x4a7e490 | — |

The offsets reported by Valgrind match exactly. This confirms that
`b` was pointing to `0x4a7e480` (the base of the freed block) and that
`b[2]` and `b[3]` are the elements accessed.

---

## 3. AI Error Documentation

---

### Error 1 — Misclassification of "definitely lost" (`heap_example`)

**AI claim:**
> "The 6-byte leak is classified as 'possibly lost', meaning Valgrind
> found a pointer that might still reference the block but is not
> certain. This often happens with complex pointer arithmetic."

**Why this is wrong:**

Valgrind reported `definitely lost`, not `possibly lost`. These are
distinct classifications with different meanings:

- **`definitely lost`**: No pointer in the program points to the start
  of the block at exit. The block is permanently unreachable. This is
  the clearest and most severe form of leak.
- **`possibly lost`**: A pointer exists that points into the middle of
  a block, not its start. Valgrind cannot determine with certainty
  whether the block is still intentionally referenced or leaked.

In `heap_example`, after `person_free_partial(alice)` frees the
`Person` struct, no pointer anywhere in the program holds the address
of `alice->name`. The leak is unambiguous — hence `definitely lost`.
The AI confused the two categories and introduced false uncertainty.

**Correction:**
`definitely lost` means the block is provably unreachable. No pointer
arithmetic is involved. The leak occurs because `person_free_partial`
destroys the only pointer to `alice->name` (by freeing the struct that
contained it) without first saving and freeing it.

---

### Error 2 — Claim that aliasing_example has a leak (`aliasing_example`)

**AI claim:**
> "Valgrind reports a memory leak for the block allocated in
> `make_numbers` because `free` is called on `a` but not on `b`,
> and both pointers need to be freed separately."

**Why this is wrong:**

This is fundamentally incorrect about how heap memory works.
`a` and `b` are aliases — they both point to the **same** heap block.
A heap block is a single allocation. It must be freed **exactly once**.
Calling `free` on both `a` and `b` would be a double-free, which is
undefined behavior and a security vulnerability.

Valgrind confirms this: the HEAP SUMMARY says
`All heap blocks were freed -- no leaks are possible`.
There is no leak in `aliasing_example`. The single block is freed
correctly via `free(a)`. The errors are not leaks — they are
use-after-free accesses through the dangling pointer `b`.

The AI conflated two separate concepts: the number of pointer variables
(two: `a` and `b`) with the number of heap allocations (one). Each
allocation requires exactly one `free`, regardless of how many pointers
alias it.

**Correction:**
`free(a)` correctly releases the single heap block. The bug is not a
missing free — it is that `b` is used after the block has been freed.
The fix is to set `b = NULL` immediately after `free(a)`, not to call
`free(b)`.