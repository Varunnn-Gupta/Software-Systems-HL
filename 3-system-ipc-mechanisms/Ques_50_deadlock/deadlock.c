#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

/* Acquire semaphore n; give up after 5 s so the demo reports the deadlock and exits. */
static int lock(int id, int n, const char *who) {
    struct sembuf op = {n, -1, 0};
    struct timespec ts = {5, 0};
    if (semtimedop(id, &op, 1, &ts) == -1) {
        if (errno == EAGAIN)
            printf("%s: timed out waiting for semaphore %d -> DEADLOCK\n", who, n);
        else
            perror("semtimedop");
        return -1;
    }
    printf("%s: acquired semaphore %d\n", who, n);
    return 0;
}

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);   /* child uses _exit(), so avoid lost buffered output */

    /* One set with two binary semaphores: 0 = resource A, 1 = resource B */
    int id = semget(IPC_PRIVATE, 2, IPC_CREAT | 0600);
    if (id == -1) { perror("semget"); return 1; }

    unsigned short init[2] = {1, 1};
    union semun arg;
    arg.array = init;
    if (semctl(id, 0, SETALL, arg) == -1) {
        perror("semctl SETALL");
        semctl(id, 0, IPC_RMID);
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) { perror("fork"); semctl(id, 0, IPC_RMID); return 1; }

    if (pid == 0) {                         /* child: A then B */
        if (lock(id, 0, "child") == -1) _exit(1);
        sleep(1);                           /* let the parent grab B */
        if (lock(id, 1, "child") == -1) _exit(1);
        printf("child: got both (never printed)\n");
        _exit(0);
    }

    /* parent: B then A (opposite order -> circular wait) */
    if (lock(id, 1, "parent") != -1) {
        sleep(1);                           /* let the child grab A */
        lock(id, 0, "parent");
    }

    waitpid(pid, NULL, 0);
    semctl(id, 0, IPC_RMID);                /* clean up the semaphore set */
    printf("Semaphore set removed\n");
    return 0;
}