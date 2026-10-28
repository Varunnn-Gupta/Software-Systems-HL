#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int p1[2], p2[2];
    if (pipe(p1) == -1 || pipe(p2) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t a = fork();
    if (a == -1) { perror("fork"); return 1; }
    if (a == 0) {
        dup2(p1[1], STDOUT_FILENO);
        close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("ls"); _exit(127);
    }

    pid_t b = fork();
    if (b == -1) { perror("fork"); return 1; }
    if (b == 0) {
        dup2(p1[0], STDIN_FILENO);
        dup2(p2[1], STDOUT_FILENO);
        close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
        execlp("grep", "grep", "^d", (char *)NULL);
        perror("grep"); _exit(127);
    }

    pid_t c = fork();
    if (c == -1) { perror("fork"); return 1; }
    if (c == 0) {
        dup2(p2[0], STDIN_FILENO);
        close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
        execlp("wc", "wc", "-l", (char *)NULL);
        perror("wc"); _exit(127);
    }

    close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
    waitpid(a, NULL, 0);
    waitpid(b, NULL, 0);
    waitpid(c, NULL, 0);
    return 0;
}
