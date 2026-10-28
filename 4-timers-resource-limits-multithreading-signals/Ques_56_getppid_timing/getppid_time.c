#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <x86intrin.h>

int main(void) {
    unsigned int aux;
    volatile pid_t result = 0;
    _mm_lfence();
    uint64_t start = __rdtsc();
    for (int i = 0; i < 100; i++)
        result = getppid();
    uint64_t end = __rdtscp(&aux);
    _mm_lfence();

    printf("Last getppid result: %ld\n", (long)result);
    printf("Ticks for 100 calls: %llu\n", (unsigned long long)(end - start));
    printf("Average ticks per call: %.2f\n", (double)(end - start) / 100.0);
    return 0;
}
