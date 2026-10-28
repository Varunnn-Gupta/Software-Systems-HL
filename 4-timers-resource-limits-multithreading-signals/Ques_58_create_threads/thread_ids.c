#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>

static void *worker(void *arg) {
    pthread_t tid = pthread_self();
    long linux_tid = syscall(SYS_gettid);
    printf("pthread_self value: %lu, Linux TID: %ld, PID: %ld\n",
           (unsigned long)tid, linux_tid, (long)getpid());
    return NULL;
}

int main(void) {
    pthread_t threads[3];
    for (int i = 0; i < 3; i++) {
        int rc = pthread_create(&threads[i], NULL, worker, NULL);
        if (rc != 0) {
            fprintf(stderr, "pthread_create: %d\n", rc);
            return 1;
        }
    }
    for (int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);
    return 0;
}
