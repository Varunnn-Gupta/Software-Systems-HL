#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat file_info;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (stat(argv[1], &file_info) == -1) {
        perror("stat");
        return 1;
    }

    printf("Inode: %ld\n", file_info.st_ino);
    printf("Number of hard links: %ld\n", file_info.st_nlink);
    printf("UID: %d\n", file_info.st_uid);
    printf("GID: %d\n", file_info.st_gid);
    printf("Size: %ld bytes\n", file_info.st_size);
    printf("Block size: %ld bytes\n", file_info.st_blksize);
    printf("Number of blocks: %ld\n", file_info.st_blocks);
    printf("Last access: %s", ctime(&file_info.st_atime));
    printf("Last modification: %s", ctime(&file_info.st_mtime));
    printf("Last change: %s", ctime(&file_info.st_ctime));

    return 0;
}
