#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char ch;
    ssize_t n;

    fd = open("input.txt", O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    while ((n = read(fd, &ch, 1)) > 0) {
        write(STDOUT_FILENO, &ch, 1);

        if (ch == '\n') {
            /* End of current line */
        }
    }

    if (n == -1) {
        perror("read");
    }

    close(fd);

    return 0;
}
