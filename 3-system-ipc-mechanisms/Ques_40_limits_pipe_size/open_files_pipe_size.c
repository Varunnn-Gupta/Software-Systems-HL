#define _GNU_SOURCE
#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    struct rlimit lim;
    if (getrlimit(RLIMIT_NOFILE, &lim) == -1) {
        perror("getrlimit");
        return 1;
    }

    printf("Soft maximum open files: ");
    if (lim.rlim_cur == RLIM_INFINITY) printf("infinity\n");
    else printf("%llu\n", (unsigned long long)lim.rlim_cur);

    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

#ifdef F_GETPIPE_SZ
    int size = fcntl(fd[0], F_GETPIPE_SZ);
    if (size == -1) perror("F_GETPIPE_SZ");
    else printf("Pipe capacity: %d bytes\n", size);
#else
    printf("F_GETPIPE_SZ is not available on this platform\n");
#endif
    close(fd[0]);
    close(fd[1]);
    return 0;
}
