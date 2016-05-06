
#include "stdio.h"
#include "3grn1.c"
main()
{
    int i, j;
    double u, g, r;
    r = 5.0;
    u = 1.0;
    g = 1.5;
    printf("\n");

    for (i = 0; i <= 9; i++) {
        for (j = 0; j <= 4; j++) {
            printf("%10.7lf  ", grn1(u, g, &r));
        }

        printf("\n");
    }

    printf("\n");
}

