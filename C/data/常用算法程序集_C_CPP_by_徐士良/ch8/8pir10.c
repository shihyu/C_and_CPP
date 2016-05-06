
#include "stdio.h"
#include "8pir1.c"
#include "math.h"
main()
{
    int i;
    double x[20], y[20], a[6], dt[3];

    for (i = 0; i <= 19; i++) {
        x[i] = 0.1 * i;
        y[i] = x[i] - exp(-x[i]);
    }

    pir1(x, y, 20, a, 6, dt);
    printf("\n");

    for (i = 0; i <= 5; i++) {
        printf("a(%2d)=%13.5e\n", i, a[i]);
    }

    printf("\n");

    for (i = 0; i <= 2; i++) {
        printf("dt(%2d)=%13.5e  ", i, dt[i]);
    }

    printf("\n\n");
}

