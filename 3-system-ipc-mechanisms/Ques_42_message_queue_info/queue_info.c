#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main(void) {
    key_t key = ftok(".", 'Q');
    if (key == (key_t)-1) { perror("ftok"); return 1; }
    int id = msgget(key, 0660);
    if (id == -1) { perror("msgget"); return 1; }

    struct msqid_ds ds;
    if (msgctl(id, IPC_STAT, &ds) == -1) { perror("msgctl"); return 1; }

    printf("Key: %ld\n", (long)ds.msg_perm.__key);
    printf("Permissions: %o\n", (unsigned int)(ds.msg_perm.mode & 0777));
    printf("UID: %u\n", (unsigned int)ds.msg_perm.uid);
    printf("GID: %u\n", (unsigned int)ds.msg_perm.gid);
    printf("Last send: %s", ctime(&ds.msg_stime));
    printf("Last receive: %s", ctime(&ds.msg_rtime));
    printf("Last change: %s", ctime(&ds.msg_ctime));
    printf("Current bytes: %lu\n", (unsigned long)ds.__msg_cbytes);
    printf("Number of messages: %lu\n", (unsigned long)ds.msg_qnum);
    printf("Maximum bytes: %lu\n", (unsigned long)ds.msg_qbytes);
    printf("Last sender PID: %ld\n", (long)ds.msg_lspid);
    printf("Last receiver PID: %ld\n", (long)ds.msg_lrpid);
    return 0;
}
