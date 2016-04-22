#include "stdio.h"
#include "r_mqr.c"
#include "r_matmul.c"
main()
{
    int i, j;
    double q[4][4], mat[4][3] = {{1.0, 2.0, 4.0},     /* 矩阵A赋值*/
        { -1.0, 0.0, 3.0}, {2.0, -1.0, 0.0}, {3.0, 1.0, 2.0}
    };
    double mat3[4][3];
    i = r_mqr(mat, 4, 3, q, 1e-16);                   /* 进行QR分解*/

    if (i != 0) {
        printf("Q:\n");                                 /* 打印Q矩阵*/

        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                printf("%2.5f ", q[i][j]);
            }

            printf("\n");
        }

        printf("\n");
        printf("R:\n");                                 /* 打印分解得到的R*/

        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                printf("%2.5f ", mat[i][j]);
            }

            printf("\n");
        }

        printf("\n");
    }

    r_matmul(q, mat, 4, 4, 3, mat3);                  /* Q*R以验证结果*/
    printf("Q*R:\n");                                 /* 打印Q*R的结果*/

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            printf("%2.5f ", mat3[i][j]);
        }

        printf("\n");
    }
}

