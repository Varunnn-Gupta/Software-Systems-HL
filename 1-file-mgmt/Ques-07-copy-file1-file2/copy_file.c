#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int src, dest;
    char buffer[100];
    ssize_t n;

    src = open("file1", O_RDONLY);

    if (src == -1) {
        perror("open file1");
        return 1;
    }

    dest = open("file2", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (dest == -1) {
        perror("open file2");
        close(src);
        return 1;
    }

    while ((n = read(src, buffer, sizeof(buffer))) > 0) {
        write(dest, buffer, n);
    }

    close(src);
    close(dest);

    return 0;
}
