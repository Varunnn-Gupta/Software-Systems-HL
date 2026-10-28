#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(void) {
    key_t key = ftok(".", 'M');
    if (key == (key_t)-1) { perror("ftok"); return 1; }
    int id = semget(key, 1, IPC_CREAT | IPC_EXCL | 0660);
    if (id == -1) { perror("semget"); return 1; }
    union semun arg;
    arg.val = 1;
    if (semctl(id, 0, SETVAL, arg) == -1) {
        perror("SETVAL");
        semctl(id, 0, IPC_RMID);
        return 1;
    }
    printf("Shared-memory semaphore ID: %d\n", id);
    return 0;
}
