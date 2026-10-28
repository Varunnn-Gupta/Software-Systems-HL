#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int main(void) {
    const char *path = "lab20_fifo";
    if (mkfifo(path, 0660) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }
    int fd = open(path, O_RDONLY);
    if (fd == -1) { perror("open"); return 1; }
    char buf[256];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    if (n == -1) { perror("read"); close(fd); return 1; }
    buf[n] = '\0';
    printf("Received: %s\n", buf);
    close(fd);
    return 0;
}
