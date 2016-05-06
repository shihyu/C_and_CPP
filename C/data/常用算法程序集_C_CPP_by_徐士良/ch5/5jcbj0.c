
#include "stdio.h"
#include "5jcbj.c"
main()
{
    int i, j;
    double eps;
    double v[5][5];
    double a[5][5] = { {10.0, 1.0, 2.0, 3.0, 4.0},
        {1.0, 9.0, -1.0, 2.0, -3.0},
        {2.0, -1.0, 7.0, 3.0, -5.0},
        {3.0, 2.0, 3.0, 12.0, -1.0},
        {4.0, -3.0, -5.0, -1.0, 15.0}
    };
    eps = 0.000001;
    jcbj(a, 5, v, eps);

    for (i = 0; i <= 4; i++) {
        printf("%13.6e\n", a[i][i]);
    }

    printf("\n\n");

    for (i = 0; i <= 4; i++) {
        for (j = 0; j <= 4; j++) {
            printf("%12.5e ", v[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

