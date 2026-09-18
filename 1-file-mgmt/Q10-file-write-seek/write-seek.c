#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    ssize_t n;
    off_t position;

    fd = open("seek_file.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    n = write(fd, "ABCDEFGHIJ", 10);

    if (n == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    position = lseek(fd, 10, SEEK_CUR);

    if (position == (off_t)-1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("lseek return value: %ld\n", (long)position);

    n = write(fd, "1234567890", 10);

    if (n == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);

    return 0;
}
