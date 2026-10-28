#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
    int p2c[2], c2p[2];
    if (pipe(p2c) == -1 || pipe(c2p) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        close(p2c[1]);
        close(c2p[0]);
        char input[128];
        ssize_t n = read(p2c[0], input, sizeof(input) - 1);
        if (n < 0) {
            perror("child read");
            return 1;
        }
        input[n] = '\0';
        printf("Child received: %s\n", input);
        const char reply[] = "Reply from child";
        if (write(c2p[1], reply, sizeof(reply)) == -1)
            perror("child write");
        close(p2c[0]);
        close(c2p[1]);
        return 0;
    }

    close(p2c[0]);
    close(c2p[1]);
    const char message[] = "Message from parent";
    if (write(p2c[1], message, sizeof(message)) == -1)
        perror("parent write");
    close(p2c[1]);

    char reply[128];
    ssize_t n = read(c2p[0], reply, sizeof(reply) - 1);
    if (n < 0) {
        perror("parent read");
        return 1;
    }
    reply[n] = '\0';
    printf("Parent received: %s\n", reply);
    close(c2p[0]);
    waitpid(pid, NULL, 0);
    return 0;
}
