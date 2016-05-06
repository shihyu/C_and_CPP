
#include "math.h"
#include "stdio.h"
#include "7csrt.c"
main()
{
    int i;
    double xr[5], xi[5];
    double ar[6] = {0.1, 21.33, 4.9, 0.0, 3.0, 1.0};
    double ai[6] = { -100.0, 0.0, -19.0, -0.01, 2.0, 0.0};
    i = csrt(ar, ai, 5, xr, xi);
    printf("\n");

    if (i > 0) {
        for (i = 0; i <= 4; i++) {
            printf("x(%d)=%13.6e j %13.6e\n", i, xr[i], xi[i]);
        }

        printf("\n");
    }
}

