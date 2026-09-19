#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct Record {
    int id;
    char name[32];
    int value;
};

int main() {
    int fd;
    struct Record records[3] = {
        {1, "Alice", 100},
        {2, "Bob", 200},
        {3, "Charlie", 300}
    };

    fd = open("records.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (write(fd, records, sizeof(records)) != sizeof(records)) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);

    return 0;
}
