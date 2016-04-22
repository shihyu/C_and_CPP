#include "stdio.h"
#include "r_chol.c"
main()
{
    int i, j;
    double u[5][5];
    double a[5][5] = { {24.0, 7.0, 5.0, 2.0, -1.0},
        {7.0, 21.0, 6.0, 3.0, -2.0}, {5.0, 6.0, 17.0, -7.0, 1.0},
        {2.0, 3.0, -7.0, 11.0, 8.0}, { -1.0, -2.0, 1.0, 8.0, 15.0}
    };   /* 矩阵A*/

    r_chol(a, 5, u, 1e-16);                                /* A相似变换为三对角阵*/
    printf("MAT u IS:\n");                                /* 打印Q矩阵*/

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%2.5f ", u[i][j]);
        }

        printf("\n");
    }

    getchar();
}
