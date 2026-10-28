#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void handler(int sig) {
    const char msg[] = "Attempted SIGSTOP handler invoked\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main(void) {
    if (signal(SIGSTOP, handler) == SIG_ERR)
        perror("signal SIGSTOP");
    printf("Receiver PID=%ld. Send SIGSTOP from the other terminal.\n",
           (long)getpid());
    fflush(stdout);
    while (1)
        pause();
}
