#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <resource-count>\n", argv[0]);
        return 1;
    }
    int count;
    if (sscanf(argv[1], "%d", &count) != 1 || count < 1) {
        fprintf(stderr, "Count must be positive\n");
        return 1;
    }
    key_t key = ftok(".", 'C');
    if (key == (key_t)-1) { perror("ftok"); return 1; }
    int id = semget(key, 1, IPC_CREAT | IPC_EXCL | 0660);
    if (id == -1) { perror("semget"); return 1; }
    union semun arg;
    arg.val = count;
    if (semctl(id, 0, SETVAL, arg) == -1) {
        perror("SETVAL");
        semctl(id, 0, IPC_RMID);
        return 1;
    }
    printf("Counting semaphore ID: %d\n", id);
    return 0;
}
