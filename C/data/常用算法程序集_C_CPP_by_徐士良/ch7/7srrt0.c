
#include "math.h"
#include "stdio.h"
#include "7srrt.c"
main()
{
    int i;
    double xr[6], xi[6];
    double a[7] = { -20.0, 7.0, -7.0, 1.0, 3.0, -5.0, 1.0};
    i = srrt(a, 6, xr, xi);
    printf("\n");

    if (i > 0) {
        for (i = 0; i <= 5; i++) {
            printf("x(%d)=%13.6e j %13.6e\n", i, xr[i], xi[i]);
        }

        printf("\n");
    }
}

