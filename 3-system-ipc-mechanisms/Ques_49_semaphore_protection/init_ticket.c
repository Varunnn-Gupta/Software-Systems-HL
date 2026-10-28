#include <stdio.h>

int main(void) {
    FILE *fp = fopen("ticket.txt", "w");
    if (!fp) { perror("fopen"); return 1; }
    if (fprintf(fp, "100\n") < 0) { perror("fprintf"); fclose(fp); return 1; }
    if (fclose(fp) == EOF) { perror("fclose"); return 1; }
    return 0;
}
