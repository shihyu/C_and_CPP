
#include "stdio.h"
#include "4ssgj.c"
#include "4trmul.c"
main()
{
    int i, j;
    double a[4][4] = { {5.0, 7.0, 6.0, 5.0},
        {7.0, 10.0, 8.0, 7.0},
        {6.0, 8.0, 10.0, 9.0},
        {5.0, 7.0, 9.0, 10.0}
    };
    double b[4][4], c[4][4];

    for (i = 0; i <= 3; i++)
        for (j = 0; j <= 3; j++) {
            b[i][j] = a[i][j];
        }

    i = ssgj(a, 4);

    if (i > 0) {
        printf("MAT A IS:\n");

        for (i = 0; i <= 3; i++) {
            for (j = 0; j <= 3; j++) {
                printf("%13.6e ", b[i][j]);
            }

            printf("\n");
        }

        printf("\n");
        printf("MAT A- IS:\n");

        for (i = 0; i <= 3; i++) {
            for (j = 0; j <= 3; j++) {
                printf("%13.6e ", a[i][j]);
            }

            printf("\n");
        }

        printf("\n");
        printf("MAT AA- IS:\n");
        trmul(b, a, 4, 4, 4, c);

        for (i = 0; i <= 3; i++) {
            for (j = 0; j <= 3; j++) {
                printf("%13.6e ", c[i][j]);
            }

            printf("\n");
        }

        printf("\n");
    }
}

