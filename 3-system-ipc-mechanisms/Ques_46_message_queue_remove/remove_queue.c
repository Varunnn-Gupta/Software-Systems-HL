#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void) {
    key_t key = ftok(".", 'Q');
    if (key == (key_t)-1) { perror("ftok"); return 1; }
    int id = msgget(key, 0660);
    if (id == -1) { perror("msgget"); return 1; }
    if (msgctl(id, IPC_RMID, NULL) == -1) { perror("IPC_RMID"); return 1; }
    printf("Message queue removed\n");
    return 0;
}
