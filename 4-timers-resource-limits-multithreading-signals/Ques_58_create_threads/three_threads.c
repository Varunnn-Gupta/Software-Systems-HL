#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static void *worker(void *arg) {
    long id = (long)arg;
    printf("Thread %ld is running\n", id);
    return NULL;
}

int main(void) {
    pthread_t threads[3];

    for (long i = 0; i < 3; i++) {
        int rc = pthread_create(&threads[i], NULL, worker, (void *)i);
        if (rc != 0) {
            fprintf(stderr, "pthread_create: %d\n", rc);
            return 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        int rc = pthread_join(threads[i], NULL);
        if (rc != 0) {
            fprintf(stderr, "pthread_join: %d\n", rc);
            return 1;
        }
    }
    return 0;
}
