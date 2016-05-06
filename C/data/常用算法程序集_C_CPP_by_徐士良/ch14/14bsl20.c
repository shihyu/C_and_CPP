
#include "stdio.h"
#include "14bsl2.c"
main()
{
    int n, i;
    double x, y;
    printf("\n");

    for (n = 0; n <= 5; n++) {
        x = 0.05;

        for (i = 1; i <= 4; i++) {
            y = bsl2(n, x);
            printf("n=%d   x=%6.3f   Y(n,x)=%13.5e\n", n, x, y);
            x = x * 10.0;
        }
    }

    printf("\n");
}

