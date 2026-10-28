#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5000

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server-ipv4>\n", argv[0]);
        return 1;
    }

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) { perror("socket"); return 1; }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, argv[1], &addr.sin_addr) != 1) {
        fprintf(stderr, "Invalid IPv4 address\n");
        close(fd);
        return 1;
    }

    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("connect"); close(fd); return 1;
    }

    const char msg[] = "Hello from client\n";
    if (write(fd, msg, sizeof(msg) - 1) == -1) perror("write");

    char buf[1024];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    if (n == -1) perror("read");
    else if (n > 0) {
        buf[n] = '\0';
        printf("Server: %s", buf);
    }
    close(fd);
    return 0;
}
