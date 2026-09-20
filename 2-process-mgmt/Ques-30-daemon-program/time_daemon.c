#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int target_hour;
    int target_minute;

    if (argc != 2)
    {
        printf("Usage: %s HH:MM\n", argv[0]);
        return 1;
    }

    if (sscanf(argv[1], "%d:%d", &target_hour, &target_minute) != 2 ||
        target_hour < 0 || target_hour > 23 ||
        target_minute < 0 || target_minute > 59)
    {
        printf("Invalid time. Use HH:MM in 24-hour format.\n");
        return 1;
    }

    if (daemon(1, 0) == -1)
    {
        perror("daemon");
        return 1;
    }

    FILE *log = fopen("daemon_task.log", "a");

    if (log == NULL)
    {
        return 1;
    }

    fprintf(log, "Daemon started. PID = %d\n", (int)getpid());
    fflush(log);

    while (1)
    {
        time_t now = time(NULL);
        struct tm current_time;

        if (localtime_r(&now, &current_time) == NULL)
        {
            fclose(log);
            return 1;
        }

        if (current_time.tm_hour == target_hour &&
            current_time.tm_min == target_minute)
        {
            fprintf(log,
                    "Task executed at %02d:%02d:%02d. PID = %d\n",
                    current_time.tm_hour,
                    current_time.tm_min,
                    current_time.tm_sec,
                    (int)getpid());

            fflush(log);
            fclose(log);
            return 0;
        }

        sleep(1);
    }
}
