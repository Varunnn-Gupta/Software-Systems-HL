#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <errno.h>

int main(void) {
    const char *path = "lab22_fifo";
    if (mkfifo(path, 0660) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    int fd = open(path, O_RDWR | O_NONBLOCK);
    if (fd == -1) { perror("open"); return 1; }

    fd_set set;
    FD_ZERO(&set);
    FD_SET(fd, &set);
    struct timeval timeout = {10, 0};

    printf("Waiting up to 10 seconds for FIFO data...\n");
    int rc = select(fd + 1, &set, NULL, NULL, &timeout);

    if (rc == -1) {
        perror("select");
        close(fd);
        return 1;
    }
    if (rc == 0) {
        printf("Timed out\n");
        close(fd);
        return 0;
    }

    char buf[256];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    if (n == -1) perror("read");
    else {
        buf[n] = '\0';
        printf("Received: %s\n", buf);
    }
    close(fd);
    return 0;
}
