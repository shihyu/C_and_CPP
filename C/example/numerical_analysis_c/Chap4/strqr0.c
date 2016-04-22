#include "stdio.h"
#include "smdqr.c"
main()
{
    int i, jt = 60;
    double eps = 0.000001;
    static double u[5], v[5];
    static double a[5][5] = { {1.0, 8.0, 0.0, 0.0, 0.0},
        {8.0, -15.0, 11.0, 0.0, 0.0},
        {0.0, 11.0, 9.0, 21.0, 0.0},
        {0.0, 0.0, 21.0, 30.0, 3.0},
        {0.0, 0.0, 0.0, 3.0, 6.0}
    };

    i = smdqr(a, 5, u, eps, jt);

    if (i > 0) {
        printf("\neigvalue:\n");

        for (i = 0; i < 5; i++) {
            printf("%e \n", u[i]);
        }

        printf("\n");
    }
}

