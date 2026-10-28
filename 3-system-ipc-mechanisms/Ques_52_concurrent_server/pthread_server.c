#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5002

static void *handle_client(void *arg) {
    int fd = *(int *)arg;
    free(arg);

    char buf[1024];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    if (n > 0) {
        buf[n] = '\0';
        printf("Thread %lu received: %s\n", (unsigned long)pthread_self(), buf);
        const char reply[] = "Handled by pthread server\n";
        if (write(fd, reply, sizeof(reply) - 1) == -1)
            perror("write");
    } else if (n == -1) {
        perror("read");
    }

    close(fd);
    return NULL;
}

int main(void) {
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

    printf("Pthread concurrent server listening on %d\n", PORT);
    for (;;) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1) { perror("accept"); continue; }

        int *arg = malloc(sizeof(*arg));
        if (arg == NULL) {
            perror("malloc");
            close(client_fd);
            continue;
        }
        *arg = client_fd;

        pthread_t thread;
        int rc = pthread_create(&thread, NULL, handle_client, arg);
        if (rc != 0) {
            fprintf(stderr, "pthread_create: %d\n", rc);
            close(client_fd);
            free(arg);
            continue;
        }
        pthread_detach(thread);
    }
}
