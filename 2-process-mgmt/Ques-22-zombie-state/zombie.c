#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child: PID = %d\n", (int)getpid());
        printf("Child exiting...\n");
        exit(0);
    }
    else
    {
        printf("Parent: PID = %d, Child PID = %d\n",
               (int)getpid(), (int)pid);

        printf("Parent sleeping. Check the child state using ps.\n");
        sleep(30);
    }

    return 0;
}
