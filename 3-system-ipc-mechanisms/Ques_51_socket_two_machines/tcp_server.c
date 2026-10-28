#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5000

int main(void) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) { perror("socket"); return 1; }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        close(server_fd);
        return 1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind"); close(server_fd); return 1;
    }
    if (listen(server_fd, 5) == -1) {
        perror("listen"); close(server_fd); return 1;
    }

    printf("Listening on port %d\n", PORT);
    int client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1) { perror("accept"); close(server_fd); return 1; }

    char buf[1024];
    ssize_t n = read(client_fd, buf, sizeof(buf) - 1);
    if (n == -1) perror("read");
    else if (n > 0) {
        buf[n] = '\0';
        printf("Client: %s\n", buf);
        const char reply[] = "Hello from server\n";
        if (write(client_fd, reply, sizeof(reply) - 1) == -1) perror("write");
    }

    close(client_fd);
    close(server_fd);
    return 0;
}
