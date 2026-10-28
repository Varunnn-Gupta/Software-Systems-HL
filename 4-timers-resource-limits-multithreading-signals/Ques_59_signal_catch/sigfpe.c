#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void handler(int sig) {
    const char msg[] = "SIGFPE received\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}


int main(void) {
    signal(SIGFPE, handler);
    raise(SIGFPE);
    return 0;
}
