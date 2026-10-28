#include <stdio.h>
#include <sys/resource.h>

int main(void) {
    struct {
        int resource;
        const char *name;
    } items[] = {
        {RLIMIT_CPU, "CPU seconds"},
        {RLIMIT_FSIZE, "File size"},
        {RLIMIT_DATA, "Data segment"},
        {RLIMIT_STACK, "Stack"},
        {RLIMIT_CORE, "Core file size"},
        {RLIMIT_RSS, "Resident set size"},
        {RLIMIT_NOFILE, "Open files"},
        {RLIMIT_AS, "Address space"}
    };

    for (unsigned long i = 0; i < sizeof(items) / sizeof(items[0]); i++) {
        struct rlimit lim;
        if (getrlimit(items[i].resource, &lim) == -1) {
            perror(items[i].name);
            continue;
        }
        printf("%s: soft=", items[i].name);
        if (lim.rlim_cur == RLIM_INFINITY) printf("infinity");
        else printf("%llu", (unsigned long long)lim.rlim_cur);
        printf(" hard=");
        if (lim.rlim_max == RLIM_INFINITY) printf("infinity");
        else printf("%llu", (unsigned long long)lim.rlim_max);
        putchar('\n');
    }
    return 0;
}
