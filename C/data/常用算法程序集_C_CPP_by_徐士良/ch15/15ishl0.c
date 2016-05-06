
#include "stdio.h"
#include "15ishl.c"
#include "3rabs.c"
main()
{
    int i, j, p[100], r0, *r, *s;
    r0 = 5;
    r = &r0;
    s = p + 30;
    rabs(100, 300, r, p, 100);
    printf("\n");

    for (i = 0; i <= 9; i++) {
        for (j = 0; j <= 9; j++) {
            printf("%d   ", p[10 * i + j]);
        }

        printf("\n");
    }

    printf("\n");
    ishl(s, 50);

    for (i = 0; i <= 9; i++) {
        for (j = 0; j <= 9; j++) {
            printf("%d   ", p[10 * i + j]);
        }

        printf("\n");
    }

    printf("\n");
}

