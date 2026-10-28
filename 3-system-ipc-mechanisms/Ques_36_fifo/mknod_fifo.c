#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void) {
    if (mknod("fifo_mknod", S_IFIFO | 0660, 0) == -1) {
        perror("mknod");
        return 1;
    }
    printf("Created fifo_mknod\n");
    return 0;
}
