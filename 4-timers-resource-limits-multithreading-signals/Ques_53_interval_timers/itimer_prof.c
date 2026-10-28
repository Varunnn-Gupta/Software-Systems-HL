#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

static void handler(int sig) {
    const char msg[] = "ITIMER_PROF expired\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main(void) {
    struct sigaction sa = {0};
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGPROF, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    struct itimerval timer = {0};
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    volatile unsigned long long n = 0;
    while (1)
        n++;
}
