#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <receiver-pid>\n", argv[0]);
        return 1;
    }
    char *end;
    long pid = strtol(argv[1], &end, 10);
    if (*end != '\0' || pid <= 0) {
        fprintf(stderr, "Invalid PID\n");
        return 1;
    }
    if (kill((pid_t)pid, SIGSTOP) == -1) {
        perror("kill");
        return 1;
    }
    printf("SIGSTOP sent to %ld\n", pid);
    return 0;
}
