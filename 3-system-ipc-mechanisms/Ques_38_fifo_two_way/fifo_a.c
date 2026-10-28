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
    int out = open("lab21_ab", O_WRONLY);
    if (out == -1) { perror("open ab"); return 1; }
    int in = open("lab21_ba", O_RDONLY);
    if (in == -1) { perror("open ba"); close(out); return 1; }
    const char msg[] = "Message from A";
    if (write(out, msg, sizeof(msg)) == -1) perror("write");
    char buf[256];
    ssize_t n = read(in, buf, sizeof(buf) - 1);
    if (n == -1) perror("read");
    else { buf[n] = '\0'; printf("A received: %s\n", buf); }
    close(out); close(in);
    return 0;
}
