
#include "stdio.h"
#include "4chol.c"
main()
{
    int i, j;
    double det;
    double a[4][4] = { {5.0, 7.0, 6.0, 5.0},
        {7.0, 10.0, 8.0, 7.0},
        {6.0, 8.0, 10.0, 9.0},
        {5.0, 7.0, 9.0, 10.0}
    };
    i = chol(a, 4, &det);

    if (i > 0) {
        printf("MAT L IS:\n");

        for (i = 0; i <= 3; i++) {
            for (j = 0; j <= 3; j++) {
                printf("%13.6e ", a[i][j]);
            }

            printf("\n");
        }

        printf("\n");
        printf("det(A)=%13.6e\n", det);
    }
}

