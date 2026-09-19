#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct stat file_info;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (lstat(argv[1], &file_info) == -1) {
        perror("lstat");
        return 1;
    }

    printf("File: %s\n", argv[1]);

    if (S_ISREG(file_info.st_mode))
        printf("Type: Regular file\n");
    else if (S_ISDIR(file_info.st_mode))
        printf("Type: Directory\n");
    else if (S_ISCHR(file_info.st_mode))
        printf("Type: Character device\n");
    else if (S_ISBLK(file_info.st_mode))
        printf("Type: Block device\n");
    else if (S_ISFIFO(file_info.st_mode))
        printf("Type: FIFO / Named pipe\n");
    else if (S_ISLNK(file_info.st_mode))
        printf("Type: Symbolic link\n");
    else if (S_ISSOCK(file_info.st_mode))
        printf("Type: Socket\n");
    else
        printf("Type: Unknown\n");

    return 0;
}
