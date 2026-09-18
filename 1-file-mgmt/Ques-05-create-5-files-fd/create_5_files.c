#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int fd[5];
	char filename[20];

	for (int i = 0; i < 5; i++) {
		sprintf(filename, "file%d.txt", i+1);

		fd[i] = open(filename, O_CREAT | O_RDWR, 0644);

		if (fd[i] == -1) {
			perror("open");
			return 1;
		}

		printf("Created %s with FD %d\n", filename, fd[i]);
	}

	while (1) {
		sleep(1);
	}

	return 0;
}
