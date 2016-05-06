
#include "stdio.h"
#include "5hhqr.c"
#include "5hhbg.c"
main()
{
    int i, j, jt = 60;
    double eps = 0.000001;
    double u[5], v[5];
    double a[5][5] = { {1.0, 6.0, -3.0, -1.0, 7.0},
        {8.0, -15.0, 18.0, 5.0, 4.0}, { -2.0, 11.0, 9.0, 15.0, 20.0},
        { -13.0, 2.0, 21.0, 30.0, -6.0}, {17.0, 22.0, -5.0, 3.0, 6.0}
    };
    hhbg(a, 5);
    printf("MAT H IS:\n");

    for (i = 0; i <= 4; i++) {
        for (j = 0; j <= 4; j++) {
            printf("%13.6e ", a[i][j]);
        }

        printf("\n");
    }

    printf("\n");
    i = hhqr(a, 5, u, v, eps, jt);

    if (i > 0)
        for (i = 0; i <= 4; i++) {
            printf("%13.6e +J %13.6e\n", u[i], v[i]);
        }

    printf("\n");
}

