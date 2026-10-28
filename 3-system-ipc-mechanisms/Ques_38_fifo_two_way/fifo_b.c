#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main(void) {
    if (mkfifo("lab21_ab", 0660) == -1 && errno != EEXIST) { perror("mkfifo ab"); return 1; }
    if (mkfifo("lab21_ba", 0660) == -1 && errno != EEXIST) { perror("mkfifo ba"); return 1; }
    int in = open("lab21_ab", O_RDONLY);
    if (in == -1) { perror("open ab"); return 1; }
    int out = open("lab21_ba", O_WRONLY);
    if (out == -1) { perror("open ba"); close(in); return 1; }
    char buf[256];
    ssize_t n = read(in, buf, sizeof(buf) - 1);
    if (n == -1) perror("read");
    else {
        buf[n] = '\0';
        printf("B received: %s\n", buf);
        const char reply[] = "Reply from B";
        if (write(out, reply, sizeof(reply)) == -1) perror("write");
    }
    close(in); close(out);
    return 0;
}
