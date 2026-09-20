#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <execl|execlp|execle|execv|execvp>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "execl") == 0)
    {
        execl("/bin/ls", "ls", "-R", "-l", (char *)NULL);
    }
    else if (strcmp(argv[1], "execlp") == 0)
    {
        execlp("ls", "ls", "-R", "-l", (char *)NULL);
    }
    else if (strcmp(argv[1], "execle") == 0)
    {
        execle("/bin/ls", "ls", "-R", "-l", (char *)NULL, environ);
    }
    else if (strcmp(argv[1], "execv") == 0)
    {
        char *args[] = {"ls", "-R", "-l", NULL};
        execv("/bin/ls", args);
    }
    else if (strcmp(argv[1], "execvp") == 0)
    {
        char *args[] = {"ls", "-R", "-l", NULL};
        execvp("ls", args);
    }
    else
    {
        printf("Invalid exec variant.\n");
        return 1;
    }

    perror("exec");
    return 1;
}
