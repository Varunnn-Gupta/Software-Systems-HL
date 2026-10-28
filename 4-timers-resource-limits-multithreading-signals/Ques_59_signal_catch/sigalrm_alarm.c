#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void handler(int sig) {
    const char msg[] = "SIGALRM received from alarm\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}


int main(void) {
    signal(SIGALRM, handler);
    alarm(5);
    while (1) pause();
}
