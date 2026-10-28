#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>

#define PORT 5001

static void handle_client(int fd) {
    char buf[1024];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    if (n > 0) {
        buf[n] = '\0';
        printf("Client PID %ld: %s\n", (long)getpid(), buf);
        const char reply[] = "Handled by fork server\n";
        write(fd, reply, sizeof(reply) - 1);
    }
    close(fd);
}

int main(void) {
    signal(SIGCHLD, SIG_IGN);
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) { perror("socket"); return 1; }
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind"); close(server_fd); return 1;
    }
    if (listen(server_fd, 10) == -1) {
        perror("listen"); close(server_fd); return 1;
    }

    printf("Fork concurrent server listening on %d\n", PORT);
    for (;;) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1) { perror("accept"); continue; }
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            close(client_fd);
            continue;
        }
        if (pid == 0) {
            close(server_fd);
            handle_client(client_fd);
            _exit(0);
        }
        close(client_fd);
    }
}
