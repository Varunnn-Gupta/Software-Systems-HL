#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t child_pids[3];
    pid_t pid;

    for (int i = 0; i < 3; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("fork");
            return 1;
        }

        if (pid == 0)
        {
            printf("Child %d: PID = %d, PPID = %d\n",
                   i + 1, (int)getpid(), (int)getppid());
            fflush(stdout);

            sleep(2 + i);
            exit(0);
        }

        child_pids[i] = pid;
    }

    printf("Parent: waiting specifically for Child 2 (PID = %d)\n",
           (int)child_pids[1]);

    int status;

    pid_t result = waitpid(child_pids[1], &status, 0);

    if (result == -1)
    {
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status))
    {
        printf("Parent: Child 2 (PID = %d) exited with status %d\n",
               (int)result, WEXITSTATUS(status));
    }

    for (int i = 0; i < 3; i++)
    {
        if (i != 1)
        {
            result = waitpid(child_pids[i], &status, 0);

            if (result == -1)
            {
                perror("waitpid");
                return 1;
            }

            printf("Parent: collected child PID = %d\n", (int)result);
        }
    }

    printf("Parent: all three children have been collected.\n");

    return 0;
}
