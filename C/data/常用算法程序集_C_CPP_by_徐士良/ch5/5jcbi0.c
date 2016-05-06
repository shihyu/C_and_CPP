
#include "stdio.h"
#include "5jcbi.c"
main()
{
    int i, j;
    double eps;
    double v[3][3];
    double a[3][3] = { {2.0, -1.0, 0.0}, { -1.0, 2.0, -1.0},
        {0.0, -1.0, 2.0}
    };
    eps = 0.000001;
    i = jcbi(a, 3, v, eps, 100);

    if (i > 0) {
        for (i = 0; i <= 2; i++) {
            printf("%13.6e  ", a[i][i]);
        }

        printf("\n\n");

        for (i = 0; i <= 2; i++) {
            for (j = 0; j <= 2; j++) {
                printf("%13.6e  ", v[i][j]);
            }

            printf("\n");
        }

        printf("\n");
    }
}

