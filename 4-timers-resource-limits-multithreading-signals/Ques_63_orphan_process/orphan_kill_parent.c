#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(void) {
    pid_t child = fork();
    if (child == -1) {
        perror("fork");
        return 1;
    }

    if (child == 0) {
        sleep(1);
        pid_t ppid = getppid();
        printf("Child %ld sending SIGKILL to parent %ld\n",
               (long)getpid(), (long)ppid);
        fflush(stdout);
        if (kill(ppid, SIGKILL) == -1) {
            perror("kill");
            return 1;
        }
        sleep(2);
        printf("Child is now orphaned; new PPID=%ld\n", (long)getppid());
        return 0;
    }

    printf("Parent PID=%ld, child PID=%ld\n",
           (long)getpid(), (long)child);
    fflush(stdout);
    while (1)
        pause();
}
