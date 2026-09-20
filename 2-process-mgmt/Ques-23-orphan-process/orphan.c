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
        printf("Child: PID = %d, Initial PPID = %d\n",
               (int)getpid(), (int)getppid());

        sleep(5);

        printf("Child: PID = %d, New PPID = %d\n",
               (int)getpid(), (int)getppid());

        sleep(20);
    }
    else
    {
        printf("Parent: PID = %d\n", (int)getpid());
        printf("Parent exiting...\n");
        exit(0);
    }

    return 0;
}
