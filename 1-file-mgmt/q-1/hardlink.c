#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    const char *oldpath = "original.txt";
    const char *newpath = "hardlink_syscall.txt";

    if (link(oldpath, newpath) == -1) {
        printf("Error creating hard link: %s\n",
               strerror(errno));
        return 1;
    }

    printf("Hard link created successfully.\n");
    return 0;
}
