#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(int argc, char **argv) {
    if (argc != 2 || argv[1][1] != '\0') {
        fprintf(stderr, "Usage: %s <key-character: T, M, or C>\n", argv[0]);
        return 1;
    }
    key_t key = ftok(".", argv[1][0]);
    if (key == (key_t)-1) { perror("ftok"); return 1; }
    int id = semget(key, 1, 0660);
    if (id == -1) { perror("semget"); return 1; }
    if (semctl(id, 0, IPC_RMID) == -1) { perror("IPC_RMID"); return 1; }
    printf("Semaphore set removed\n");
    return 0;
}
