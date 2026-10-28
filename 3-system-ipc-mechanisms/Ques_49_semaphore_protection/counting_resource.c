#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <semaphore-id>\n", argv[0]);
        return 1;
    }
    int id = atoi(argv[1]);
    struct sembuf acquire = {0, -1, 0};
    struct sembuf release = {0, 1, 0};

    while (semop(id, &acquire, 1) == -1) {
        if (errno == EINTR) continue;
        perror("acquire");
        return 1;
    }

    printf("PID %ld acquired one pseudo-resource\n", (long)getpid());
    sleep(2);
    printf("PID %ld releasing one pseudo-resource\n", (long)getpid());

    if (semop(id, &release, 1) == -1) {
        perror("release");
        return 1;
    }
    return 0;
}
