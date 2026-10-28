#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void) {
    if (mkfifo("fifo_mkfifo", 0660) == -1) {
        perror("mkfifo");
        return 1;
    }
    printf("Created fifo_mkfifo\n");
    return 0;
}
