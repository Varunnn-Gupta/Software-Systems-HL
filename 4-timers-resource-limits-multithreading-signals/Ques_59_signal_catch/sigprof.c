#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

static void handler(int sig) {
    const char msg[] = "SIGPROF received from ITIMER_PROF\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}


int main(void) {
    signal(SIGPROF, handler);
    struct itimerval t = {0};
    t.it_value.tv_sec = 2;
    if (setitimer(ITIMER_PROF, &t, NULL) == -1) {
        perror("setitimer");
        return 1;
    }
    volatile unsigned long long n = 0;
    while (1) n++;
}
