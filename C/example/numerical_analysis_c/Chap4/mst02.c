#include "stdio.h"
#include "mhhbg.c"
main()
{
    int i, j;
    static double q[5][5];
    static double b[5][5] = { {12.0, 7.0, 5.0, 2.0, -1.0},    /* 矩阵B*/
        {8.0, 9.0, 6.0, 3.0, -2.0}, {4.0, 3.0, 5.0, -7.0, 1.0},
        {2.0, 5.0, 7.0, -1.0, 8.0}, {1.0, 2.0, 3.0, 9.0, 2.0}
    };
    mhhbg(b, 5, q, 1e-16);                               /* B相似变换为上HB阵*/
    printf("MAT Q IS:\n");

    for (i = 0; i <= 4; i++) {                           /* 打印Q矩阵*/
        for (j = 0; j <= 4; j++) {
            printf("%2.5f ", q[i][j]);
        }

        printf("\n");
    }

    printf("\n");
    printf("MAT HHBG IS:\n");

    for (i = 0; i <= 4; i++) {                           /* 打印相似变换的结果*/
        for (j = 0; j <= 4; j++) {
            printf("%2.5f ", b[i][j]);
        }

        printf("\n");
    }
}
