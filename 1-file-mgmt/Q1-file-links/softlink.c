#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    const char *target = "original.txt";
    const char *linkpath = "softlink_syscall.txt";

    if (symlink(target, linkpath) == -1) {
        printf("Error creating symbolic link: %s\n",
               strerror(errno));
        return 1;
    }

    printf("Symbolic link created successfully.\n");
    return 0;
}

