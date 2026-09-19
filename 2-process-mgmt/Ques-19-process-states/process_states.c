#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Process started. PID = %d\n", getpid());
    printf("Process is now running. Press Ctrl+Z to stop it.\n");
    fflush(stdout);

    while (1)
    {
        /* Busy loop keeps the process runnable/running. */
    }

    return 0;
}
