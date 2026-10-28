#include <stdio.h>
#include <unistd.h>
#include <errno.h>

static void show(const char *name, int key) {
    errno = 0;
    long value = sysconf(key);
    if (value == -1 && errno != 0)
        perror(name);
    else if (value == -1)
        printf("%s: indeterminate\n", name);
    else
        printf("%s: %ld\n", name, value);
}

int main(void) {
    show("Maximum argument length", _SC_ARG_MAX);
    show("Maximum simultaneous processes per user", _SC_CHILD_MAX);
    show("Clock ticks per second", _SC_CLK_TCK);
    show("Maximum open files", _SC_OPEN_MAX);
    show("Page size", _SC_PAGESIZE);
    show("Physical memory pages", _SC_PHYS_PAGES);
    show("Available physical memory pages", _SC_AVPHYS_PAGES);
    return 0;
}
