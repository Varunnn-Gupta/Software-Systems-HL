#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <binary|counting> <count>\n", argv[0]);
        return 1;
    }

    int count;
    if (sscanf(argv[2], "%d", &count) != 1 || count < 0) {
        fprintf(stderr, "Invalid count\n");
        return 1;
    }
    if (argv[1][0] == 'b')
        count = 1;

    key_t key = ftok(".", 'M');
    if (key == (key_t)-1) { perror("ftok"); return 1; }

    int id = semget(key, 1, IPC_CREAT | IPC_EXCL | 0660);
    if (id == -1) { perror("semget"); return 1; }

    union semun arg;
    arg.val = count;
    if (semctl(id, 0, SETVAL, arg) == -1) {
        perror("semctl SETVAL");
        semctl(id, 0, IPC_RMID);
        return 1;
    }

    printf("Semaphore ID: %d\nInitial value: %d\n", id, count);
    return 0;
}
