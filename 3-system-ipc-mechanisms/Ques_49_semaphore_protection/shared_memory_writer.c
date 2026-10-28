#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

static int down(int id) {
    struct sembuf op = {0, -1, 0};
    while (semop(id, &op, 1) == -1) {
        if (errno == EINTR) continue;
        perror("semop down");
        return -1;
    }
    return 0;
}

static int up(int id) {
    struct sembuf op = {0, 1, 0};
    if (semop(id, &op, 1) == -1) { perror("semop up"); return -1; }
    return 0;
}

int main(int argc, char **argv) {
    key_t skey = ftok(".", 'M');
    key_t hkey = ftok(".", 'H');
    if (skey == (key_t)-1 || hkey == (key_t)-1) { perror("ftok"); return 1; }

    int semid = semget(skey, 1, 0660);
    int shmid = shmget(hkey, 1024, 0660);
    if (semid == -1 || shmid == -1) { perror("semget/shmget"); return 1; }

    char *p = shmat(shmid, NULL, 0);
    if (p == (void *)-1) { perror("shmat"); return 1; }

    if (down(semid) == -1) { shmdt(p); return 1; }
    snprintf(p, 1024, "Written by PID %ld, message=%s",
             (long)getpid(), argc > 1 ? argv[1] : "default");
    printf("Updated shared memory: %s\n", p);
    int rc = up(semid);
    shmdt(p);
    return rc == -1 ? 1 : 0;
}
