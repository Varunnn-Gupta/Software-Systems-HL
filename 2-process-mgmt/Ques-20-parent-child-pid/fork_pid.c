#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

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
        printf("Child: PID = %d, Parent PID = %d\n",
               (int)getpid(), (int)getppid());
    }
    else
    {
        printf("Parent: PID = %d, Child PID = %d\n",
               (int)getpid(), (int)pid);
    }

    return 0;
}
