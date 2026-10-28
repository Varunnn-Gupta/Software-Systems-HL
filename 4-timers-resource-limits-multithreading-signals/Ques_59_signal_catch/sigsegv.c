#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void handler(int sig) {
    const char msg[] = "SIGSEGV received\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}


int main(void) {
    signal(SIGSEGV, handler);
    raise(SIGSEGV);
    return 0;
}
