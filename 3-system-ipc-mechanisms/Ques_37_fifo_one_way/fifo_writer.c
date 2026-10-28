#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(void) {
    const char *path = "lab20_fifo";
    if (mkfifo(path, 0660) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }
    int fd = open(path, O_WRONLY);
    if (fd == -1) { perror("open"); return 1; }
    const char msg[] = "Hello through FIFO";
    if (write(fd, msg, sizeof(msg)) == -1) perror("write");
    close(fd);
    return 0;
}
