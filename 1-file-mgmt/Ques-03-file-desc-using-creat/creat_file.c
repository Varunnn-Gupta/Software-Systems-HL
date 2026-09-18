#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    fd = creat("sample.txt", 0644);

    if (fd == -1) {
        perror("creat");
        return 1;
    }

    printf("File descriptor: %d\n", fd);

    close(fd);

    return 0;
}
