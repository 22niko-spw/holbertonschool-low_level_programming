# Memory Maps — AI Memory Visualizer

> **Methodology**: Each program was compiled with `-Wall -Wextra -pedantic -std=gnu89 -g`
> and executed to collect real addresses. AI was used to generate initial memory maps,
> then each map was reviewed and corrected manually. All AI errors are documented explicitly.

---

## Table of Contents

1. [stack\_example.c](#1-stack_examplec)
2. [aliasing\_example.c](#2-aliasing_examplec)
3. [heap\_example.c](#3-heap_examplec)
4. [AI Error Documentation](#4-ai-error-documentation)

---

## 1. `stack_example.c`

### Program overview

`walk_stack()` calls itself recursively from depth 0 to 3.
At each level it calls `dump_frame()`, which creates its own stack frame.
The program prints the address of every local variable, making the stack layout
observable at runtime.

### Real addresses collected at runtime

```
walk_stack depth=0   &marker = 0xfffff2865394
  dump_frame enter   &local_int = 0xfffff286534c   local_buf = 0xfffff2865358

walk_stack depth=1   &marker = 0xfffff2865364
  dump_frame enter   &local_int = 0xfffff286531c   local_buf = 0xfffff2865328

walk_stack depth=2   &marker = 0xfffff2865334
  dump_frame enter   &local_int = 0xfffff28652ec   local_buf = 0xfffff28652f8

walk_stack depth=3   &marker = 0xfffff2865304
  dump_frame enter   &local_int = 0xfffff28652bc   local_buf = 0xfffff28652c8
```

Each recursive level is allocated **at a lower address** than the previous one,
confirming that the stack grows downward on this architecture.

Address delta between consecutive `walk_stack` frames:
`0xfffff2865394 - 0xfffff2865364 = 0x30` (48 bytes) per level.

---

### Step-by-step memory map

#### Step 1 — `main()` calls `walk_stack(0, 3)`

```
STACK (grows downward ↓)
High addresses
┌─────────────────────────────────────────────┐
│  main() frame                               │
│    (return address, saved registers)        │
├─────────────────────────────────────────────┤
│  walk_stack(depth=0) frame                  │
│    depth     = 0                            │
│    max_depth = 3                            │
│    marker    = 0        @ 0xfffff2865394   │
└─────────────────────────────────────────────┘
Low addresses
```

- `marker` is a local `int` — it lives only as long as this call of
  `walk_stack` is active.
- Its address is valid here but becomes invalid once `walk_stack(0, 3)` returns.

---

#### Step 2 — `walk_stack(0,3)` calls `dump_frame("enter", 0)`

A new frame is pushed **below** the `walk_stack(0)` frame:

```
STACK
┌─────────────────────────────────────────────┐
│  main() frame                               │
├─────────────────────────────────────────────┤
│  walk_stack(depth=0) frame                  │
│    marker    = 0        @ 0xfffff2865394   │
├─────────────────────────────────────────────┤
│  dump_frame("enter", depth=0) frame         │
│    label     = ptr to "enter"               │
│    depth     = 0                            │
│    local_int = 100      @ 0xfffff286534c   │
│    local_buf[16]        @ 0xfffff2865358   │
│    p_local   = 0xfffff286534c  (alias!)    │
└─────────────────────────────────────────────┘
Low addresses
```

**Aliasing inside `dump_frame`:**
`p_local` is declared as `int *p_local = &local_int`.
Both `p_local` and `local_int` refer to the same stack cell at `0xfffff286534c`.
This alias is **safe here** because both live in the same frame and neither
outlives it.

---

#### Step 3 — Recursion unfolds: depth 0 → 1 → 2 → 3

```
STACK (all frames active at peak depth = 3)
High addresses
┌──────────────────────────────────────────────────┐
│ main()                                           │
├──────────────────────────────────────────────────┤
│ walk_stack(0)   marker=0    @ 0xfffff2865394    │
├──────────────────────────────────────────────────┤
│ walk_stack(1)   marker=10   @ 0xfffff2865364    │
├──────────────────────────────────────────────────┤
│ walk_stack(2)   marker=20   @ 0xfffff2865334    │
├──────────────────────────────────────────────────┤
│ walk_stack(3)   marker=30   @ 0xfffff2865304    │
├──────────────────────────────────────────────────┤
│ dump_frame(depth=3)                              │
│   local_int=103 @ 0xfffff28652bc               │
│   local_buf[16] @ 0xfffff28652c8               │
│   p_local       = 0xfffff28652bc               │
└──────────────────────────────────────────────────┘
Low addresses
```

---

#### Step 4 — Unwinding: depth 3 returns, then 2, then 1, then 0

When `walk_stack(3)` returns, its entire frame is popped.
`marker` at `0xfffff2865304` is no longer valid memory for the program.
The stack pointer moves back up. `walk_stack(2)` resumes — its own
`marker` at `0xfffff2865334` is still valid.

```
STACK after depth=3 returns
┌──────────────────────────────────────────────────┐
│ main()                                           │
├──────────────────────────────────────────────────┤
│ walk_stack(0)   marker=0    @ 0xfffff2865394    │
├──────────────────────────────────────────────────┤
│ walk_stack(1)   marker=10   @ 0xfffff2865364    │
├──────────────────────────────────────────────────┤
│ walk_stack(2)   marker=20   @ 0xfffff2865334    │  ← active frame
├──────────────────────────────────────────────────┤
│  [popped — no longer valid]                      │  ← was walk_stack(3)
└──────────────────────────────────────────────────┘
Low addresses
```

> **Key point**: the memory at the old `walk_stack(3)` address is **not erased**.
> It may still contain the old values, but reading it is undefined behavior.
> Any subsequent function call can and will overwrite that region.

The runtime output confirms this: at `[exit] depth=3`, the addresses and values
are identical to `[enter] depth=3` — because nothing has overwritten them yet.
This does **not** mean the memory is still valid.

---

#### Variable lifetime summary — `stack_example`

| Variable | Scope | Lifetime | Location |
|---|---|---|---|
| `depth`, `max_depth` | `walk_stack` frame | Duration of that call | Stack |
| `marker` | `walk_stack` frame | Duration of that call | Stack |
| `local_int` | `dump_frame` frame | Duration of `dump_frame` call | Stack |
| `local_buf[16]` | `dump_frame` frame | Duration of `dump_frame` call | Stack |
| `p_local` | `dump_frame` frame | Duration of `dump_frame` call | Stack |

No heap allocations. No pointers escape their frame. Program is memory-safe.

---

## 2. `aliasing_example.c`

### Program overview

`make_numbers(5)` allocates an array of 5 integers on the heap.
`a` receives the pointer. Then `b = a` creates an alias.
`free(a)` is called. After that, `b` is used to read and write —
this is a **use-after-free** bug.

### Real addresses collected at runtime

```
a = 0xaaaaba2816b0
b = 0xaaaaba2816b0   (same — alias confirmed)
a[2] = 22, b[2] = 22
After free(a): b[2] = -872835351  (garbage — heap block poisoned by allocator)
b[3] written: 1234
```

---

### Step-by-step memory map

#### Step 1 — `make_numbers(5)` is called

```
STACK                               HEAP
┌───────────────────────┐          ┌──────────────────────────────────┐
│ make_numbers frame    │          │ int[5] @ 0xaaaaba2816b0          │
│   n   = 5             │          │  [0] =  0                        │
│   i   = 0..4          │  arr ───►│  [1] = 11                        │
│   arr = 0xaaaaba2816b0│          │  [2] = 22                        │
└───────────────────────┘          │  [3] = 33                        │
                                   │  [4] = 44                        │
                                   └──────────────────────────────────┘
```

`arr` is a stack variable that holds the address of a heap block.
The heap block's lifetime is **not tied to the stack frame** — it persists
until explicitly freed.

---

#### Step 2 — Back in `main`: `a = make_numbers(5)`, then `b = a`

```
STACK                               HEAP
┌───────────────────────┐          ┌──────────────────────────────────┐
│ main frame            │          │ int[5] @ 0xaaaaba2816b0          │
│   a = 0xaaaaba2816b0  │────┐     │  [0] =  0                        │
│   b = 0xaaaaba2816b0  │────┴────►│  [1] = 11                        │
│   n = 5               │          │  [2] = 22  ← a[2] == b[2]       │
└───────────────────────┘          │  [3] = 33                        │
                                   │  [4] = 44                        │
                                   └──────────────────────────────────┘
```

`a` and `b` are **aliases**: two distinct stack variables holding the same
heap address. There is a single heap block with two owners — dangerous.

**Ownership problem**: only one pointer should be responsible for freeing
the block. The programmer calls `free(a)` but does not clear `b` afterward.

---

#### Step 3 — `free(a)` is called

```
STACK                               HEAP
┌───────────────────────┐          ┌──────────────────────────────────┐
│ main frame            │          │ [FREED BLOCK] @ 0xaaaaba2816b0  │
│   a = 0xaaaaba2816b0  │──╳──►   │  contents: UNDEFINED             │
│   b = 0xaaaaba2816b0  │──╳──►   │  (overwritten by allocator       │
│   n = 5               │          │   metadata)                      │
└───────────────────────┘          └──────────────────────────────────┘
         ↑ DANGLING POINTERS
```

After `free(a)`:
- The heap block is returned to the allocator. Its contents are **undefined**.
- `a` still holds `0xaaaaba2816b0` — it is now a **dangling pointer**.
- `b` also holds `0xaaaaba2816b0` — it is also a **dangling pointer**.
- Neither pointer is NULL. Dereferencing either is **undefined behavior**.

`free()` did **not** modify `a` or `b`. It only changed the state of the
heap block they point to.

---

#### Step 4 — `b[2]` is read (use-after-free read)

```c
printf("  reading b[2]=%d\n", b[2]);   /* line 42 */
```

At runtime: `b[2]` printed `-872835351` instead of `22`.

The allocator writes internal bookkeeping data into freed blocks.
The value `-872835351` is a fragment of the allocator's internal
linked-list pointer reinterpreted as a signed `int`.

The read does not crash here because the memory page is still mapped
(the allocator keeps freed blocks in its own free-list rather than
returning the page to the OS immediately). This behavior is
implementation-defined and cannot be relied upon.

---

#### Step 5 — `b[3] = 1234` is written (use-after-free write)

```c
b[3] = 1234;   /* line 44 */
```

This **corrupts allocator metadata**. If the allocator later attempts
to coalesce or reuse this block, it may read the corrupted metadata and
crash unpredictably — in an entirely unrelated part of the program.

```
HEAP (corrupted)
┌──────────────────────────────────┐
│ [FREED BLOCK] @ 0xaaaaba2816b0  │
│  [0] = ??? (allocator data)     │
│  [1] = ??? (allocator data)     │
│  [2] = ??? (allocator data)     │
│  [3] = 1234  ← CORRUPTED       │
│  [4] = ???                      │
└──────────────────────────────────┘
```

---

#### Variable and ownership summary — `aliasing_example`

| Variable | Location | Points to | Valid after `free(a)`? |
|---|---|---|---|
| `a` | Stack (main) | Heap block @ 0xaaaaba2816b0 | No — dangling |
| `b` | Stack (main) | Heap block @ 0xaaaaba2816b0 | No — dangling |
| `arr` (in `make_numbers`) | Stack (destroyed on return) | Same heap block | N/A — frame gone |

**The correct fix:**

```c
free(a);
a = NULL;
b = NULL;   /* b was an alias — it must also be invalidated */
```

---

## 3. `heap_example.c`

### Program overview

`person_new()` allocates two heap blocks per `Person`: one for the `Person`
struct itself, one for the `name` string. `bob` is freed correctly (both
blocks). `alice` is freed via `person_free_partial()` which only frees
the `Person` struct — **leaking `alice->name`**.

---

### Step-by-step memory map

#### Step 1 — After `person_new("Alice", 30)`

```
STACK                          HEAP
┌──────────────────┐          ┌──────────────────────────────────┐
│ main frame       │          │ Person struct (alice)            │
│  alice ──────────┼─────────►│   name ──────────────────────┐  │
│  bob  = NULL     │          │   age  = 30                   │  │
└──────────────────┘          └──────────────────────────────┼─┘
                               ┌──────────────────────────────▼──┐
                               │ char[6] — "Alice\0"             │
                               └─────────────────────────────────┘
```

Two heap allocations exist for Alice:
1. The `Person` struct (contains pointer `name` and `int age`).
2. The `char` array for the name string, pointed to by `p->name`.

These are **separate blocks** linked by an internal pointer.
Freeing only the struct without freeing `name` first creates a leak.

---

#### Step 2 — After `person_new("Bob", 41)`

```
HEAP
┌──────────────────────────────────┐
│ Person struct (alice)            │
│   name ──► char[6] "Alice\0"    │
│   age  = 30                      │
├──────────────────────────────────┤
│ Person struct (bob)              │
│   name ──► char[4] "Bob\0"      │
│   age  = 41                      │
└──────────────────────────────────┘
```

Four heap blocks are now live. Each `Person` owns its `name` block.

---

#### Step 3 — `free(bob->name)` then `free(bob)` — correct order

```
HEAP
┌──────────────────────────────────┐
│ Person struct (alice)  LIVE      │
│   name ──► char[6]     LIVE      │
├──────────────────────────────────┤
│ char[4] "Bob\0"        FREED     │  ← freed first (correct)
├──────────────────────────────────┤
│ Person struct (bob)    FREED     │  ← freed second (correct)
└──────────────────────────────────┘
```

`name` must be freed **before** the struct, because freeing the struct
first makes `bob->name` inaccessible (the pointer is inside the freed struct).

---

#### Step 4 — `person_free_partial(alice)` — the leak

`person_free_partial` only calls `free(p)` — it does not free `p->name`.

```
HEAP after person_free_partial(alice)
┌──────────────────────────────────┐
│ Person struct (alice)  FREED     │  ← struct freed
│  (former name ptr lost)          │  ← pointer no longer accessible
├──────────────────────────────────┤
│ char[6] "Alice\0"      LEAKED    │  ← NEVER freed — unreachable
└──────────────────────────────────┘
```

The `char[6]` block is now **unreachable**:
- The only pointer to it (`alice->name`) lived inside the `Person` struct.
- That struct has been freed.
- No other variable holds the address of the name block.
- The block can never be freed — it is a **permanent memory leak**.

Valgrind would report: `6 bytes in 1 block definitely lost`.

---

#### Heap allocation/free summary — `heap_example`

| Block | Size | Freed? |
|---|---|---|
| alice — Person struct | sizeof(Person) | Yes (partial free) |
| alice — name string | 6 bytes ("Alice\0") | **NO — LEAKED** |
| bob — Person struct | sizeof(Person) | Yes |
| bob — name string | 4 bytes ("Bob\0") | Yes |

---

## 4. AI Error Documentation

This section documents cases where the initial AI-generated explanation
was incorrect or incomplete, and the manual correction applied.

---

### Error 1 — Stack frames are zeroed on deallocation (`stack_example`)

**AI claim:**
> "When `walk_stack(3)` returns, its local variables are destroyed and
> their memory is zeroed out, making the addresses safe to reuse."

**Why this is wrong:**

Stack frames are not zeroed on deallocation. The stack pointer simply
moves back — the bytes at those addresses remain intact until the next
function call overwrites them.

The runtime output confirms this directly: at `[exit] depth=3`, the
program prints the exact same values as `[enter] depth=3` —
`local_int=103`, `local_buf[0]=D`, `marker=30` — because nothing has
overwritten them yet. This looks correct but is misleading: the memory
is no longer valid, it just happens to be untouched.

**Correction:**
Stack deallocation is purely a stack-pointer adjustment. No memory is
cleared. The lifetime of a local variable ends when its enclosing function
returns, regardless of what bytes remain at that address.

---

### Error 2 — Only `a` becomes dangling after `free(a)` (`aliasing_example`)

**AI claim:**
> "After `free(a)`, only `a` becomes invalid. Since `b` was assigned
> before the free, it retains its own independent copy of the pointer
> and remains valid."

**Why this is wrong:**

`b = a` copies the **pointer value** (the address `0xaaaaba2816b0`), not
the heap block. Both `a` and `b` point to the same memory. `free(a)`
deallocates that memory. The fact that `b` was assigned before the free
is completely irrelevant.

Validity is a property of the **target memory**, not of the pointer variable.
Both `a` and `b` are dangling after `free(a)`.

The runtime output confirms this: `b[2]` returned `-872835351` instead
of `22`, because the allocator had already modified the freed block.

**Correction:**
When two pointers alias the same heap block, freeing through either one
invalidates both. After `free(a)`, both `a` and `b` must be treated as
dangling pointers and must not be dereferenced under any circumstances.

---

### Error 3 — Wrong identification of the leaked block (`heap_example`)

**AI claim:**
> "The memory leak is caused by `free(bob)` being called before
> `free(bob->name)`, which loses the reference to the name string."

**Why this is wrong:**

This is incorrect on two counts. First, the program frees bob correctly:
`free(bob->name)` is called first, then `free(bob)` — the order is right.
Second, the actual leak concerns **alice**, not bob. `person_free_partial(alice)`
frees the `Person` struct without first freeing `alice->name`, leaving
6 bytes permanently unreachable.

**Correction:**
The leaked block is `alice->name` (6 bytes, "Alice\0"). It is leaked
because `person_free_partial` calls `free(p)` without saving and freeing
`p->name` first. Once the struct is freed, the only pointer to the name
allocation is gone and the block can never be recovered.