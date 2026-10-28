#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void) {
    struct sigaction sa = {0};
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction ignore");
        return 1;
    }

    printf("SIGINT ignored for 5 seconds. Try Ctrl+C.\n");
    sleep(5);

    sa.sa_handler = SIG_DFL;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction default");
        return 1;
    }

    printf("Default SIGINT action restored. Press Ctrl+C.\n");
    while (1)
        pause();
}
