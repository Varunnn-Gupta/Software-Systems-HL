#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Sleeping process started. PID = %d\n", getpid());
    fflush(stdout);

    while (1)
    {
        sleep(10);
    }

    return 0;
}
