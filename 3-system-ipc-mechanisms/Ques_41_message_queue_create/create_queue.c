#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void) {
    key_t key = ftok(".", 'Q');
    if (key == (key_t)-1) { perror("ftok"); return 1; }
    int msqid = msgget(key, IPC_CREAT | 0660);
    if (msqid == -1) { perror("msgget"); return 1; }
    printf("Key: %ld\n", (long)key);
    printf("Message queue ID: %d\n", msqid);
    return 0;
}
