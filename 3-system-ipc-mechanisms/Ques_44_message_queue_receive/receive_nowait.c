#include <stdio.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long mtype;
    char mtext[128];
};

int main(void) {
    key_t key = ftok(".", 'Q');
    if (key == (key_t)-1) { perror("ftok"); return 1; }
    int id = msgget(key, 0660);
    if (id == -1) { perror("msgget"); return 1; }
    struct message msg;
    ssize_t n = msgrcv(id, &msg, sizeof(msg.mtext), 0, IPC_NOWAIT);
    if (n == -1) {
        if (errno == ENOMSG) {
            printf("No message available\\n");
            return 0;
        }
        perror("msgrcv");
        return 1;
    }
    printf("Received type %ld: %s\\n", msg.mtype, msg.mtext);
    return 0;
}
