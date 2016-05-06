
#include "stdio.h"
#include "4ginv.c"
main()
{
    int m, n, ka, i, j;
    double a[5][4] = { {1.0, 2.0, 3.0, 4.0},
        {6.0, 7.0, 8.0, 9.0}, {1.0, 2.0, 13.0, 0.0},
        {16.0, 17.0, 8.0, 9.0}, {2.0, 4.0, 3.0, 4.0}
    };
    double aa[4][5], c[5][4], u[5][5], v[4][4];
    double eps;
    m = 5;
    n = 4;
    ka = 6;
    eps = 0.000001;
    printf("MAT A IS:\n");

    for (i = 0; i <= 4; i++) {
        for (j = 0; j <= 3; j++) {
            printf("%13.6e ", a[i][j]);
        }

        printf("\n");
    }

    printf("\n");
    printf("MAT A+ IS:\n");
    i = ginv(a, m, n, aa, eps, u, v, ka);

    if (i > 0) {
        for (i = 0; i <= 3; i++) {
            for (j = 0; j <= 4; j++) {
                printf("%12.5e ", aa[i][j]);
            }

            printf("\n");
        }

        printf("\n");
    }

    printf("MAT A++ IS:\n");
    i = ginv(aa, n, m, c, eps, v, u, ka);

    if (i > 0) {
        for (i = 0; i <= 4; i++) {
            for (j = 0; j <= 3; j++) {
                printf("%13.6e ", c[i][j]);
            }

            printf("\n");
        }

        printf("\n");
    }
}

