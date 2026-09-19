#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, dup_fd;

    fd = open("append3.txt", O_WRONLY | O_APPEND);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    dup_fd = fcntl(fd, F_DUPFD, 10);

    if (dup_fd == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Original FD: %d\n", fd);
    printf("Duplicated FD: %d\n", dup_fd);

    write(fd, "Written using original FD.\n", 28);
    write(dup_fd, "Written using fcntl FD.\n", 24);

    close(fd);
    close(dup_fd);

    return 0;
}
