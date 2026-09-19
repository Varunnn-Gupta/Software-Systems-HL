#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main() {
    fd_set readfds;
    struct timeval timeout;
    char buffer[100];
    int result;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input from STDIN for 10 seconds...\n");
    fflush(stdout);

    result = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (result == -1) {
        perror("select");
        return 1;
    }

    if (result == 0) {
        printf("No input received within 10 seconds.\n");
        return 0;
    }

    if (FD_ISSET(STDIN_FILENO, &readfds)) {
        ssize_t n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

        if (n > 0) {
            buffer[n] = '\0';
            printf("Data available on STDIN.\n");
            printf("Input: %s", buffer);
        }
    }

    return 0;
}
