#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

struct Record {
    int id;
    char name[32];
    int value;
};

int main(int argc, char *argv[]) {
    int fd;
    int record_no;
    char mode;
    struct Record record;
    struct flock lock;
    off_t offset;

    if (argc != 3) {
        printf("Usage: %s <record_no> <r/w>\n", argv[0]);
        return 1;
    }

    record_no = atoi(argv[1]);
    mode = argv[2][0];

    if (record_no < 1 || record_no > 3) {
        printf("Record number must be 1, 2, or 3.\n");
        return 1;
    }

    if (mode == 'w')
        fd = open("records.dat", O_RDWR);
    else if (mode == 'r')
        fd = open("records.dat", O_RDONLY);
    else {
        printf("Mode must be r or w.\n");
        return 1;
    }

    if (fd == -1) {
        perror("open");
        return 1;
    }

    offset = (record_no - 1) * sizeof(struct Record);

    lock.l_type = (mode == 'w') ? F_WRLCK : F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = offset;
    lock.l_len = sizeof(struct Record);
    lock.l_pid = getpid();

    printf("Process %d requesting %s lock on record %d...\n",
           getpid(),
           (mode == 'w') ? "write" : "read",
           record_no);

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Lock acquired on record %d.\n", record_no);
    printf("Holding lock for 10 seconds...\n");

    sleep(10);

    lseek(fd, offset, SEEK_SET);

    if (read(fd, &record, sizeof(record)) != sizeof(record)) {
        perror("read");
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);
        return 1;
    }

    if (mode == 'r') {
        printf("ID: %d\n", record.id);
        printf("Name: %s\n", record.name);
        printf("Value: %d\n", record.value);
    } else {
        record.value++;

        lseek(fd, offset, SEEK_SET);

        if (write(fd, &record, sizeof(record)) != sizeof(record)) {
            perror("write");
        } else {
            printf("Record %d modified.\n", record_no);
            printf("New value: %d\n", record.value);
        }
    }

    lock.l_type = F_UNLCK;

    if (fcntl(fd, F_SETLK, &lock) == -1)
        perror("unlock");
    else
        printf("Lock released.\n");

    close(fd);

    return 0;
}
