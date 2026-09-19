#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    struct flock lock;

    fd = open("lockfile.txt", O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    printf("Requesting read lock...\n");

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Read lock acquired. PID: %d\n", getpid());
    printf("Holding lock for 20 seconds...\n");

    sleep(20);

    lock.l_type = F_UNLCK;

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("unlock");
    } else {
        printf("Read lock released.\n");
    }

    close(fd);

    return 0;
}
