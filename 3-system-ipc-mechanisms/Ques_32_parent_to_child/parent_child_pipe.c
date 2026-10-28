#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        close(fd[1]);
        char buffer[256];
        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);
        if (n == -1) {
            perror("read");
            return 1;
        }
        buffer[n] = '\0';
        printf("Child received: %s\n", buffer);
        close(fd[0]);
        return 0;
    }

    close(fd[0]);
    const char msg[] = "Message from parent";
    if (write(fd[1], msg, sizeof(msg)) == -1)
        perror("write");
    close(fd[1]);
    waitpid(pid, NULL, 0);
    return 0;
}
