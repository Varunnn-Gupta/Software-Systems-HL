#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>

static int down(int id) {
    struct sembuf op = {0, -1, 0};
    while (semop(id, &op, 1) == -1) {
        if (errno == EINTR) continue;
        perror("semop down");
        return -1;
    }
    return 0;
}

static int up(int id) {
    struct sembuf op = {0, 1, 0};
    if (semop(id, &op, 1) == -1) { perror("semop up"); return -1; }
    return 0;
}

int main(void) {
    key_t key = ftok(".", 'T');
    if (key == (key_t)-1) { perror("ftok"); return 1; }
    int id = semget(key, 1, 0660);
    if (id == -1) { perror("semget"); return 1; }

    FILE *fp = fopen("ticket.txt", "r+");
    if (!fp) { perror("fopen"); return 1; }

    if (down(id) == -1) { fclose(fp); return 1; }

    int value;
    rewind(fp);
    if (fscanf(fp, "%d", &value) != 1) {
        fprintf(stderr, "Invalid ticket file\n");
        up(id);
        fclose(fp);
        return 1;
    }

    value++;
    rewind(fp);
    if (fprintf(fp, "%d\n", value) < 0 || fflush(fp) == EOF) {
        perror("ticket write");
        up(id);
        fclose(fp);
        return 1;
    }

    printf("Reserved ticket: %d\n", value);
    int rc = up(id);
    fclose(fp);
    return rc == -1 ? 1 : 0;
}
