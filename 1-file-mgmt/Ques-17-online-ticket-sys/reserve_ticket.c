#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    int ticket;
    char buffer[32];
    ssize_t n;
    struct flock lock;

    fd = open("ticket.txt", O_RDWR);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    printf("Process %d requesting write lock...\n", getpid());

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Process %d acquired write lock.\n", getpid());
    printf("Holding lock for 5 seconds...\n");

    sleep(5);

    lseek(fd, 0, SEEK_SET);

    n = read(fd, buffer, sizeof(buffer) - 1);

    if (n <= 0) {
        perror("read");
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);
        return 1;
    }

    buffer[n] = '\0';
    ticket = atoi(buffer);
    ticket++;

    lseek(fd, 0, SEEK_SET);
    ftruncate(fd, 0);
    dprintf(fd, "%d\n", ticket);

    printf("New ticket number: %d\n", ticket);

    lock.l_type = F_UNLCK;

    if (fcntl(fd, F_SETLK, &lock) == -1)
        perror("unlock");
    else
        printf("Process %d released write lock.\n", getpid());

    close(fd);

    return 0;
}
