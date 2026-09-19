#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, flags, access_mode;

    fd = open("test.txt", O_RDWR);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    flags = fcntl(fd, F_GETFL);

    if (flags == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    access_mode = flags & O_ACCMODE;

    printf("File descriptor: %d\n", fd);
    printf("Opening mode: ");

    if (access_mode == O_RDONLY)
        printf("Read Only\n");
    else if (access_mode == O_WRONLY)
        printf("Write Only\n");
    else if (access_mode == O_RDWR)
        printf("Read Write\n");

    close(fd);

    return 0;
}
