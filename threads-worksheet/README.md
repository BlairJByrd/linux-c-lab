# Threads and Context Switching – Worksheet

Build and run:
```bash
./build.sh
./run_all.sh
```

## 1.1 Hello World
Prints `My pid is X` once or twice, always the same pid (threads share one process).
The child thread only prints if it runs before `main` returns, since returning from
`main` calls `exit()` and kills every thread.

## 3.1 Join
Possible outputs: HELPER then MAIN; MAIN then HELPER; or only MAIN.
`pthread_yield()` is only a hint. Fix: replace it with `pthread_join(thread, NULL);`.

## 3.2 Stack Allocation
`i is 2` – the thread writes to main's stack variable through a pointer (shared address space).

## 3.3 Heap Allocation
`I am the child` – the heap is shared, so the child overwrites the same buffer.

## 3.4 Threads and Processes
Three lines: the child process prints `Data is 1` (its own copy after fork); the parent
prints `Data is 1` then `Data is 2`. The child's line can appear anywhere in that order.

Return value:
```c
void *ret;
pthread_join(thread, &ret);
printf("%d\n", (int)(intptr_t) ret);   // 42
```

## 3.5 Context Switching
1. Two stacks: the current thread's kernel stack and the next thread's kernel stack.
   switch_threads pushes ebx/ebp/esi/edi on the current stack, saves esp into cur->stack,
   loads esp from next->stack, pops next's registers, and returns into the next thread.
2. The stack is LIFO, so intr_exit must pop in the exact reverse order of intr_entry's
   pushes, matching struct intr_frame. Otherwise registers get wrong values
   (e.g. a bad segment selector causes a general protection fault).

## 3.6 Reflections on Threads
1. A web server handling many clients (threads overlap I/O); parallel computation such as
   matrix multiplication or image processing on multiple cores.
2. ULTs are managed in user space (cheap switches, but one blocking syscall blocks all and
   no multicore parallelism). KLTs are kernel-scheduled (true parallelism, one blocking
   doesn't stop others, but costlier switches). ULTs suit many light, non-blocking tasks;
   KLTs suit I/O-heavy or parallel work.
3. Trap/interrupt enters the kernel, registers are saved on the kernel stack, the scheduler
   picks the next thread, callee-saved registers are pushed and esp saved in the old TCB,
   esp loaded from the new TCB and its registers popped, page tables switched if it's a
   different process, then return (iret to user mode).
4/5. A thread needs a TCB, a stack, and registers; it shares code, heap, globals, files, and
   the address space. A process needs a PCB, a new address space/page table, a
   (copy-on-write) copy of memory, its own file table, and a first thread – much heavier.
