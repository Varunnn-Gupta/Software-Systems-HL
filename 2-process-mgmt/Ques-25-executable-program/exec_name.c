#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    }

    printf("Executing a.out...\n");
    fflush(stdout);

    execl("./a.out", "a.out", argv[1], (char *)NULL);

    perror("execl");
    return 1;
}
