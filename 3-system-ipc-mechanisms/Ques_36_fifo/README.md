Shell commands:

```bash
mknod myfifo p
mkfifo myfifo
strace -e mknod,mknodat,mkfifo mkfifo myfifo2
```

`mkfifo` is the simpler, purpose-built interface for creating a FIFO. `mknod` is more general. Exact system calls visible under `strace` depend on libc and kernel implementation; `mkfifo()` may internally use `mknodat()`.

Remove old FIFOs with `rm -f myfifo myfifo2`.
