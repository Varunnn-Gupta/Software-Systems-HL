#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void) {
    if (signal(SIGINT, SIG_IGN) == SIG_ERR) {
        perror("signal ignore");
        return 1;
    }
    printf("SIGINT ignored for 5 seconds. Try Ctrl+C.\n");
    sleep(5);

    if (signal(SIGINT, SIG_DFL) == SIG_ERR) {
        perror("signal default");
        return 1;
    }
    printf("Default SIGINT action restored. Press Ctrl+C.\n");
    while (1)
        pause();
}
