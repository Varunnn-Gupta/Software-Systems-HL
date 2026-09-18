#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main() {
    const char *pathname = "fifo_mkfifo";

    if (mkfifo(pathname, 0666) == -1) {
        printf("Error creating FIFO: %s\n",
               strerror(errno));
        return 1;
    }

    printf("FIFO created successfully.\n");
    return 0;
}
