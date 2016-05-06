
#include "stdio.h"
#include "14gass.c"
main()
{
    int i, j;
    double a0, d0, x, y;
    double a[2] = { -1.0, 3.0};
    double d[2] = { 0.5, 15.0};
    printf("\n");

    for (i = 0; i <= 1; i++) {
        a0 = a[i];
        d0 = d[i];
        x = -10.0;

        for (j = 0; j <= 4; j++) {
            y = gass(a0, d0, x);
            printf("P(%4.2f, %4.2f, %4.2f)=%13.5e\n", a0, d0, x, y);
            x = x + 5.0;
        }
    }

    printf("\n");
}

