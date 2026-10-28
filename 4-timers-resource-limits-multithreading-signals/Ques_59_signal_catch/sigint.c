#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void handler(int sig) {
    const char msg[] = "SIGINT received\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}


int main(void) {
    signal(SIGINT, handler);
    printf("Press Ctrl+C to send SIGINT\n");
    while (1) pause();
}
