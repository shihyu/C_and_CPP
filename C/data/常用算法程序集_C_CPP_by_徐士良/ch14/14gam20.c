
#include "stdio.h"
#include "14gam2.c"
main()
{
    int i, j;
    double y, s, t;
    double a[3] = {0.5, 5.0, 50.0};
    double x[3] = {0.1, 1.0, 10.0};
    printf("\n");

    for (i = 0; i <= 2; i++)
        for (j = 0; j <= 2; j++) {
            s = a[i];
            t = x[j];
            y = gam2(s, t);
            printf("gamma(%4.1f,%4.1f)=%13.5e\n", a[i], x[j], y);
        }

    printf("\n");
}


