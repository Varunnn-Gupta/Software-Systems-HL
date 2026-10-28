#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main(void) {
    key_t key = ftok(".", 'S');
    if (key == (key_t)-1) { perror("ftok"); return 1; }

    int id = shmget(key, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0600);
    if (id == -1) { perror("shmget"); return 1; }

    char *writer = shmat(id, NULL, 0);
    if (writer == (void *)-1) {
        perror("shmat writer");
        shmctl(id, IPC_RMID, NULL);
        return 1;
    }

    strcpy(writer, "Hello from shared memory");
    printf("Written: %s\n", writer);

    const char *reader = shmat(id, NULL, SHM_RDONLY);
    if (reader == (void *)-1) {
        perror("shmat reader");
        shmdt(writer);
        shmctl(id, IPC_RMID, NULL);
        return 1;
    }

    printf("Read-only mapping: %s\n", reader);
    printf("Writing through this mapping is not attempted because it is read-only.\n");

    if (shmdt(reader) == -1) perror("shmdt reader");
    if (shmdt(writer) == -1) perror("shmdt writer");
    if (shmctl(id, IPC_RMID, NULL) == -1) { perror("IPC_RMID"); return 1; }
    printf("Shared memory removed\n");
    return 0;
}
