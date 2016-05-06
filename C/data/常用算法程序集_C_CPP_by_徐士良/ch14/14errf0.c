
#include "stdio.h"
#include "14errf.c"
main()
{
    int i, j;
    double x, y;
    printf("\n");

    for (i = 0; i <= 9; i++) {
        for (j = 0; j <= 3; j++) {
            x = 0.05 * (4.0 * i + j);
            y = errf(x);
            printf("erf(%4.2f)=%8.6f ", x, y);
        }

        printf("\n");
    }

    x = 2.0;
    y = errf(x);
    printf("erf(%4.2f)=%8.6f\n", x, y);
    printf("\n");
}

