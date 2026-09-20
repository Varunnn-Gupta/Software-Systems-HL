#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("PID = %d\n", (int)getpid());
    printf("Process is running. Press Ctrl+C to terminate.\n");
    fflush(stdout);

    while (1)
    {
    }

    return 0;
}
