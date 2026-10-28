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

    const char text[] = "Hello through pipe";
    if (write(fd[1], text, sizeof(text)) == -1) {
        perror("write");
        return 1;
    }
    close(fd[1]);

    char buffer[128];
    ssize_t n = read(fd[0], buffer, sizeof(buffer));
    if (n == -1) {
        perror("read");
        close(fd[0]);
        return 1;
    }
    printf("Read %zd bytes: %s\n", n, buffer);
    close(fd[0]);
    return 0;
}
