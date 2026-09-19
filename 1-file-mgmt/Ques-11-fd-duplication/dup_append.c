#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, dup_fd;

    fd = open("append.txt", O_WRONLY | O_APPEND);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    dup_fd = dup(fd);

    if (dup_fd == -1) {
        perror("dup");
        close(fd);
        return 1;
    }

    printf("Original FD: %d\n", fd);
    printf("Duplicated FD: %d\n", dup_fd);

    write(fd, "Written using original FD.\n", 28);
    write(dup_fd, "Written using duplicated FD.\n", 30);

    close(fd);
    close(dup_fd);

    return 0;
}
