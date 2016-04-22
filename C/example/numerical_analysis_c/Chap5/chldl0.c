#include "stdio.h"
#include "r_chde.c"
#include "r_ldl.c"
main()
{
    int i, j;
    double a[5][5] = { {24.0, 7.0, 5.0, 2.0, -1.0},
        {7.0, 21.0, 6.0, 3.0, -2.0}, {5.0, 6.0, 17.0, -7.0, 1.0},
        {2.0, 3.0, -7.0, 11.0, 8.0}, { -1.0, -2.0, 1.0, 8.0, 15.0}
    };   /* 矩阵A */
    double b[5] = {4.0, 6.5, 1.5, -2.5, 12.0}, x[5];     /* 常量向量赋值*/
    /*这两个算法不破坏数据，因此不需要拷贝*/
    r_ldl(a, b, x, 5, 1e-16);                            /* 调用LDL分解法求解*/
    printf("LDL DECO:\n");                               /* 打印LDL分解法的结果*/

    for (i = 0; i < 5; i++) {
        printf("%2.5f\n", x[i]);
    }

    printf("\n");
    r_chde(a, b, x, 5, 1e-16);                           /* 调用Cholesky分解法求解*/
    printf("CHOLESKY:\n");                               /* 打印Cholesky分解法的结果*/

    for (i = 0; i < 5; i++) {
        printf("%2.5f\n", x[i]);
    }
}
