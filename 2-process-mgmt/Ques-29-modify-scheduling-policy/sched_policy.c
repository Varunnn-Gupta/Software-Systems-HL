#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>

const char *policy_name(int policy)
{
    switch (policy)
    {
        case SCHED_OTHER:
            return "SCHED_OTHER";
        case SCHED_FIFO:
            return "SCHED_FIFO";
        case SCHED_RR:
            return "SCHED_RR";
        default:
            return "UNKNOWN";
    }
}

int main(int argc, char *argv[])
{
    int current_policy;
    int new_policy;
    struct sched_param param;

    current_policy = sched_getscheduler(0);

    if (current_policy == -1)
    {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Current scheduling policy: %s\n",
           policy_name(current_policy));

    if (argc != 2)
    {
        printf("Usage: %s <fifo|rr>\n", argv[0]);
        return 0;
    }

    if (strcmp(argv[1], "fifo") == 0)
        new_policy = SCHED_FIFO;
    else if (strcmp(argv[1], "rr") == 0)
        new_policy = SCHED_RR;
    else
    {
        printf("Invalid policy. Use fifo or rr.\n");
        return 1;
    }

    param.sched_priority = sched_get_priority_min(new_policy);

    if (sched_setscheduler(0, new_policy, &param) == -1)
    {
        perror("sched_setscheduler");
        return 1;
    }

    current_policy = sched_getscheduler(0);

    if (current_policy == -1)
    {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Modified scheduling policy: %s\n",
           policy_name(current_policy));
    printf("Scheduling priority: %d\n", param.sched_priority);

    return 0;
}
