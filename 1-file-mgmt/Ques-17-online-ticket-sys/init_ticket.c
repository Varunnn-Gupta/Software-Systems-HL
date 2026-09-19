#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    int ticket = 100;

    fd = open("ticket.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    dprintf(fd, "%d\n", ticket);

    close(fd);

    return 0;
}
