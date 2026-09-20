#include <stdio.h>
#include <sched.h>

int main(void)
{
    int min_priority;
    int max_priority;

    min_priority = sched_get_priority_min(SCHED_FIFO);
    max_priority = sched_get_priority_max(SCHED_FIFO);

    if (min_priority == -1)
    {
        perror("sched_get_priority_min");
        return 1;
    }

    if (max_priority == -1)
    {
        perror("sched_get_priority_max");
        return 1;
    }

    printf("Minimum real-time priority: %d\n", min_priority);
    printf("Maximum real-time priority: %d\n", max_priority);

    return 0;
}
