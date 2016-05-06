
#include "stdio.h"
#include "5sstq.c"
#include "5strq.c"
main()
{
    int i, j, k, l = 60;
    double q[5][5], b[5], c[5];
    double a[5][5] = { {10.0, 1.0, 2.0, 3.0, 4.0},
        {1.0, 9.0, -1.0, 2.0, -3.0}, {2.0, -1.0, 7.0, 3.0, -5.0},
        {3.0, 2.0, 3.0, 12.0, -1.0}, {4.0, -3.0, -5.0, -1.0, 15.0}
    };
    double eps = 0.000001;
    strq(a, 5, q, b, c);
    k = sstq(5, b, c, q, eps, l);
    printf("MAT A IS:\n");

    for (i = 0; i <= 4; i++) {
        for (j = 0; j <= 4; j++) {
            printf("%13.6e ", a[i][j]);
        }

        printf("\n");
    }

    printf("\n");

    if (k > 0) {
        printf("MAT B IS:\n");

        for (i = 0; i <= 4; i++) {
            printf("%13.6e ", b[i]);
        }

        printf("\n\n");
        printf("MAT Q IS:\n");

        for (i = 0; i <= 4; i++) {
            for (j = 0; j <= 4; j++) {
                printf("%13.6e ", q[i][j]);
            }

            printf("\n");
        }

        printf("\n");
    }
}

