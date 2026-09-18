#include <unistd.h>

int main() {
    char buffer[100];
    ssize_t n;

    while ((n = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, n);
    }

    return 0;
}
