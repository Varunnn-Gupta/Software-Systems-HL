#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, dup_fd;

    fd = open("append2.txt", O_WRONLY | O_APPEND);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    dup_fd = dup2(fd, 10);

    if (dup_fd == -1) {
        perror("dup2");
        close(fd);
        return 1;
    }

    printf("Original FD: %d\n", fd);
    printf("Duplicated FD: %d\n", dup_fd);

    write(fd, "Written using original FD.\n", 28);
    write(dup_fd, "Written using dup2 FD.\n", 23);

    close(fd);
    close(dup_fd);

    return 0;
}
