# Crash Report — `crash_example`

> **Program:** `crash_example`
> **Compiled with:** `-Wall -Wextra -Werror -pedantic -std=gnu89 -g`
> **Observed behavior:** Segmentation fault (signal 11 / SIGSEGV)
> **Valgrind version:** 3.22.0

---

## 1. Crash Description

The program terminates immediately with a segmentation fault after
printing two lines:

```
crash_example: deterministic NULL dereference (segmentation fault)
  requesting n=0
Segmentation fault
```

Valgrind confirms:

```
==50975== Invalid write of size 4
==50975==    at 0x10893C: main (crash_example.c:32)
==50975==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==50975== Process terminating with default action of signal 11 (SIGSEGV)
==50975==  Access not within mapped region at address 0x0
```

The crash is **deterministic**: given the same input (`n = 0`), it
will always crash at the same instruction. It is not a race condition,
not a stack overflow, and not hardware-dependent.

---

## 2. Root Cause Analysis

### The invalid memory access

The crash occurs at **`crash_example.c:32`**:

```c
nums[0] = 42;
```

At this point, `nums` holds the value `NULL` (address `0x0`).
Writing to `nums[0]` is equivalent to writing to address
`0x0 + 0 * sizeof(int) = 0x0`.
Address `0x0` is never mapped in the virtual address space of a
user-space process. Writing to it triggers a hardware memory protection
fault, which the OS delivers to the process as SIGSEGV (signal 11),
terminating it immediately.

---

### Full causal chain

**Step 1 — `n` is initialized to 0**

```c
int n = 0;   /* line 23 */
```

`n` is a local variable on the stack in `main`. Its value is explicitly
set to `0` at declaration. This is not an uninitialized variable issue —
the value `0` is intentional in the source code.

**Step 2 — `allocate_numbers(0)` is called**

```c
nums = allocate_numbers(n);   /* line 29 */
```

`allocate_numbers` receives `n = 0`. Its first action is a guard check:

```c
if (n <= 0)
    return NULL;
```

Because `n = 0` satisfies `n <= 0`, the function immediately returns
`NULL` without calling `malloc`. No heap allocation is made.

**Step 3 — `nums` receives `NULL`**

Back in `main`, `nums` is now `NULL`. At this point:

```
STACK
┌──────────────────────────┐
│ main frame               │
│   n    = 0               │
│   nums = NULL (0x0)      │  ← no heap block exists
└──────────────────────────┘

HEAP
  (empty — no allocation was made)
```

**Step 4 — The return value of `allocate_numbers` is not checked**

The code proceeds directly to:

```c
nums[0] = 42;   /* line 32 */
```

There is no `if (!nums)` guard between line 29 and line 32.
The programmer assumed `allocate_numbers` would always return a valid
pointer, but the function explicitly returns `NULL` for `n <= 0`.

**Step 5 — NULL dereference causes SIGSEGV**

`nums[0] = 42` computes the target address as:
`NULL + 0 * sizeof(int) = 0x0`

The CPU attempts to write 4 bytes to virtual address `0x0`.
This address is in the null page, which is intentionally left unmapped
by the OS as a trap for exactly this class of bug.
The memory management unit raises a page fault.
The OS catches it, determines the access is invalid (not mapped,
not writable), and sends SIGSEGV to the process.
The process terminates with "Segmentation fault".

---

### Memory state at crash

```
STACK at crash (line 32)
┌──────────────────────────────────────────┐
│ main frame                               │
│   n    = 0                               │
│   nums = 0x0  (NULL)   ← INVALID PTR   │
└──────────────────────────────────────────┘

HEAP
  (no allocation — allocate_numbers returned early)

ATTEMPTED ACCESS
  Write 4 bytes to address 0x0  ← NOT MAPPED → SIGSEGV
```

---

### Category of undefined behavior

**NULL pointer dereference** — writing through a pointer that holds
the value `NULL` (address `0x0`).

This is a specific case of **invalid memory access**: the pointer is
not dangling (it does not point to freed memory), and it is not
uninitialized (its value is explicitly `NULL`). The bug is a missing
return-value check: the caller does not verify that the callee
succeeded before using the returned pointer.

---

## 3. Valgrind Output Interpretation

```
Invalid write of size 4
   at 0x10893C: main (crash_example.c:32)
 Address 0x0 is not stack'd, malloc'd or (recently) free'd
```

- **`Invalid write of size 4`**: a 4-byte write (one `int`) to an
  address that Valgrind does not recognize as valid memory.
- **`Address 0x0`**: the exact address written to — confirming NULL
  dereference, not an off-by-one or a dangling pointer.
- **`not stack'd, malloc'd or (recently) free'd`**: the address has
  never been part of a stack frame, never been allocated by `malloc`,
  and has not been recently freed. It is simply unmapped.

The HEAP SUMMARY shows `1 allocs, 0 frees` — the 1,024-byte block
is `stdio` internal buffering (not from the program), listed as
`still reachable` (not a leak). The program made **zero** calls to
`malloc` itself before crashing.

---

## 4. AI Critique

### AI claim 1 — "The crash is caused by a buffer overflow"

**Incorrect.**

A buffer overflow involves writing past the end of a validly allocated
buffer. Here, no buffer was ever allocated. `allocate_numbers(0)`
returned `NULL` before calling `malloc`. There is no buffer to overflow.
The crash is a NULL dereference, not a buffer overflow. These are
distinct categories of memory misuse with different causes and
mitigations.

---

### AI claim 2 — "The segfault occurs because `malloc` returned NULL
due to insufficient memory"

**Incorrect.**

`malloc` is never called in this execution. `allocate_numbers` returns
`NULL` at the guard check `if (n <= 0) return NULL`, before reaching
the `malloc` call. The Valgrind HEAP SUMMARY confirms this:
`total heap usage: 1 allocs` — and that single allocation is from
the C standard library's internal stdio buffer, not from the program.
The AI incorrectly assumed the failure was inside `malloc`, when in
fact the function returned early before `malloc` was ever reached.

---

## 5. Suggested Fix

> *This section is labeled as a suggested fix and is not part of the
> required crash analysis.*

The fix requires checking the return value of `allocate_numbers`
before dereferencing the pointer:

```c
nums = allocate_numbers(n);
if (!nums)                          /* add this check */
{
    fprintf(stderr, "allocation failed or n <= 0\n");
    return 1;
}
nums[0] = 42;
```

A more robust approach also prevents `n = 0` from being passed in the
first place, by validating input before calling the function.

The underlying design issue is that `allocate_numbers` silently returns
`NULL` for invalid input without any indication to the caller. A
well-documented function contract (or an assertion) would make this
failure mode explicit.