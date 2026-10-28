#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long mtype;
    char mtext[128];
};

int main(int argc, char **argv) {
    key_t key = ftok(".", 'Q');
    if (key == (key_t)-1) { perror("ftok"); return 1; }
    int id = msgget(key, IPC_CREAT | 0660);
    if (id == -1) { perror("msgget"); return 1; }

    struct message msg;
    msg.mtype = 1;
    const char *text = argc > 1 ? argv[1] : "Hello from sender";
    snprintf(msg.mtext, sizeof(msg.mtext), "%s", text);

    if (msgsnd(id, &msg, strlen(msg.mtext) + 1, 0) == -1) {
        perror("msgsnd");
        return 1;
    }
    printf("Sent: %s\n", msg.mtext);
    return 0;
}
