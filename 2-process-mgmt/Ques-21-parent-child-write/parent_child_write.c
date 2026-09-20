#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int fd = open("parent_child.txt",
                  O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        close(fd);
        return 1;
    }

    if (pid == 0)
    {
        const char message[] = "Child process writing to file.\n";

        if (write(fd, message, sizeof(message) - 1) == -1)
        {
            perror("write");
            close(fd);
            return 1;
        }
    }
    else
    {
        const char message[] = "Parent process writing to file.\n";

        if (write(fd, message, sizeof(message) - 1) == -1)
        {
            perror("write");
            close(fd);
            return 1;
        }

        wait(NULL);
    }

    close(fd);
    return 0;
}
