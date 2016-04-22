/*======================================================
//函数名：eulerinvh
//功能描述：定步长欧拉算法求常微分方程组的初值问题
//输入参数：*y（ 指向函数初值以及函数返回值的指针n*(m+1)）
//          n（方程组个数），f（目标函数的计算）
//          h（步长），m（步数），a（区间起点）
//返回值：0（失败），1（成功）
=========================================================*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int eulerinvh(y, n, f, h, m, a)
double* y, (*f)(), h, a;
int n, m;
{
    double* F, x;
    int k = 0, i;
    F = (double*)malloc(sizeof(double) * n); /* 微分方程表达式的值*/

    if (F == NULL) {
        printf("memory alloc failed.\n");
        return (0);
    }

    do {
        x = a + k * h;
        f(&y[k * n], F, x);                  /* 计算微分方程表达式的值*/

        for (i = 0; i < n; i++) {
            y[(k + 1)*n + i] = y[k * n + i] + h * F[i];    /* 计算此处的函数值*/
        }

        k++;
    } while (k < m);

    free(F);
    return (1);
}
