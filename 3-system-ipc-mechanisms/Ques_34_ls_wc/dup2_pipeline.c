#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) { perror("pipe"); return 1; }
    pid_t p1 = fork();
    if (p1 == -1) { perror("fork"); return 1; }
    if (p1 == 0) {
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1) { perror("dup2"); _exit(1); }
        close(fd[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        _exit(127);
    }
    pid_t p2 = fork();
    if (p2 == -1) { perror("fork"); return 1; }
    if (p2 == 0) {
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1) { perror("dup2"); _exit(1); }
        close(fd[0]);
        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc");
        _exit(127);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    return 0;
}
