
#include "stdio.h"
#include "6gmqr.c"
main()
{
    int i, m, n;
    double a[4][3] = { {1.0, 1.0, -1.0}, {2.0, 1.0, 0.0},
        {1.0, -1.0, 0.0}, { -1.0, 2.0, 1.0}
    };
    double b[4] = {2.0, -3.0, 1.0, 4.0};
    double q[4][4];
    m = 4;
    n = 3;
    i = gmqr(a, m, n, b, q);

    if (i != 0) {
        for (i = 0; i <= 2; i++) {
            printf("x(%d)=%13.6e\n", i, b[i]);
        }

        printf("\n");
        printf("MAT Q IS:\n");

        for (i = 0; i <= 3; i++)
            printf("%13.6e %13.6e %13.6e %13.6e\n",
                   q[i][0], q[i][1], q[i][2], q[i][3]);

        printf("\n");
        printf("MAT R IS:\n");

        for (i = 0; i <= 3; i++)
            printf("%13.6e %13.6e %13.6e\n",
                   a[i][0], a[i][1], a[i][2]);
    }
}

