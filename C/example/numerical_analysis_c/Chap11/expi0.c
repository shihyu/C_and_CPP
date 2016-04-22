#include "stdio.h"
#include "expi.c"
main()
{
    int i, j, ni;
    double xj, y;
    double e1 = 1.0e-7;             /* 这两个值用于不完全伽马函数的计算*/
    int n[3] = {1, 2, 3};
    double x[3] = {0.5, 1.0, 5.0};

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            ni = n[i];                               /* 循环取a和x*/
            xj = x[j];
            y = expi(ni, xj, e1);                    /* 调用函数求值并打印结果*/
            printf("E(%d,%1.1f)=%e ", ni, xj, y);
        }

        printf("\n");
    }

    getchar();
}
