/*======================================================
//功能描述：3种线性多步方法求常微分方程组的初值问题的例子
=========================================================*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include "adams.c"
#include "hamming.c"
#include "bb.c"

void main()
{
    double h = 0.01, a = 0, eps = 0.000000001;
    int n = 3, m = 10, i, j;
    double* y;                    /* 存放所有函数值的指针*/
    void f(double*, double*, double);
    y = (double*)malloc(n * (m + 1) * sizeof(double));

    for (i = 0; i < n * (m + 1); i++) { /* 初始化*/
        y[i] = 0.0;
    }

    y[0] = -1.0;                   /* 初值*/
    y[1] = 0.0;
    y[2] = 1.0;

    if (adams(y, n, f, h, m, a)) {
        printf("阿当姆斯预报校正法求值\n");

        for (i = 0; i <= m; i++) {
            printf("x=%1.2f ", a + h * i);

            for (j = 0; j < n; j++) {
                printf("y[%d]=%1.9f  ", j, y[3 * i + j]);    /* 输出*/
            }

            printf("\n");
        }
    } else {
        printf("failed!\n");
    }

    if (hamming(y, n, f, h, m, a)) {
        printf("哈明算法求值\n");

        for (i = 0; i <= m; i++) {
            printf("x=%1.2f ", a + h * i);

            for (j = 0; j < n; j++) {
                printf("y[%d]=%1.9f  ", j, y[3 * i + j]);    /* 输出*/
            }

            printf("\n");
        }
    } else {
        printf("failed!\n");
    }

    if (bb(y, n, f, h, m, a)) {
        printf("双边法求值\n");

        for (i = 0; i <= m; i++) {
            printf("x=%1.2f ", a + h * i);

            for (j = 0; j < n; j++) {
                printf("y[%d]=%1.9f  ", j, y[3 * i + j]);    /* 输出*/
            }

            printf("\n");
        }
    } else {
        printf("failed!\n");
    }

    free(y);
}
void f(y, F, x)
double* y, *F, x;
{
    F[0] = 5 * x + 1;
    F[1] = x + y[0];
    F[2] = -1 * y[2];
    return;
}
