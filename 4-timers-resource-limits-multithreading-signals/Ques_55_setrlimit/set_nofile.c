#include <stdio.h>
#include <sys/resource.h>

int main(void) {
    struct rlimit lim;
    if (getrlimit(RLIMIT_NOFILE, &lim) == -1) {
        perror("getrlimit");
        return 1;
    }

    printf("Old soft limit: %llu\n", (unsigned long long)lim.rlim_cur);
    printf("Old hard limit: %llu\n", (unsigned long long)lim.rlim_max);

    rlim_t desired = 64;
    if (desired > lim.rlim_max)
        desired = lim.rlim_max;
    lim.rlim_cur = desired;

    if (setrlimit(RLIMIT_NOFILE, &lim) == -1) {
        perror("setrlimit");
        return 1;
    }

    if (getrlimit(RLIMIT_NOFILE, &lim) == -1) {
        perror("getrlimit");
        return 1;
    }

    printf("New soft limit: %llu\n", (unsigned long long)lim.rlim_cur);
    printf("New hard limit: %llu\n", (unsigned long long)lim.rlim_max);
    return 0;
}
