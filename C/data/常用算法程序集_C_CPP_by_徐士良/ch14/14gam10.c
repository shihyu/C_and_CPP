
#include "stdio.h"
#include "14gam1.c"
main()
{
    int i;
    double x, y;
    printf("\n");

    for (i = 1; i <= 10; i++) {
        x = 0.5 * i;
        y = gam1(x);
        printf("x=%6.3f  gamma(x)=%13.5e\n", x, y);
    }

    printf("\n");
    y = gam1(1.5) * gam1(2.5) / gam1(4.0);
    printf("B(1.5,2.5)=%13.5e\n", y);
    printf("\n");
}

