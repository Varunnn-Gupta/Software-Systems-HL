#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

static void handler(int sig) {
    const char msg[] = "SIGALRM received from ITIMER_REAL\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}


int main(void) {
    signal(SIGALRM, handler);
    struct itimerval t = {0};
    t.it_value.tv_sec = 5;
    if (setitimer(ITIMER_REAL, &t, NULL) == -1) {
        perror("setitimer");
        return 1;
    }
    while (1) pause();
}
