
#include "stdio.h"
#include "6grad.c"
main()
{
    int i;
    double eps, x[4];
    double a[4][4] = {{5.0, 7.0, 6.0, 5.0},
        {7.0, 10.0, 8.0, 7.0},
        {6.0, 8.0, 10.0, 9.0},
        {5.0, 7.0, 9.0, 10.0}
    };
    double b[4] = {23.0, 32.0, 33.0, 31.0};
    eps = 0.000001;
    grad(a, 4, b, eps, x);
    printf("\n");

    for (i = 0; i <= 3; i++) {
        printf("x[%d]=%13.5e\n", i, x[i]);
    }

    printf("\n");
}

