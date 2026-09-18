#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main() {
    const char *pathname = "fifo_mknod";

    if (mknod(pathname, S_IFIFO | 0666, 0) == -1) {
        printf("Error creating FIFO: %s\n",
               strerror(errno));
        return 1;
    }

    printf("FIFO created successfully using mknod().\n");
    return 0;
}
