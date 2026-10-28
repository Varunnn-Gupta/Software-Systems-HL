#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(void) {
    key_t key = ftok(".", 'H');
    if (key == (key_t)-1) { perror("ftok"); return 1; }
    int id = shmget(key, 1024, IPC_CREAT | 0660);
    if (id == -1) { perror("shmget"); return 1; }
    char *p = shmat(id, NULL, 0);
    if (p == (void *)-1) { perror("shmat"); return 1; }
    memset(p, 0, 1024);
    strcpy(p, "initial");
    printf("Initialized shared memory\n");
    shmdt(p);
    return 0;
}
