/*======================================================
//函数名：euleradv
//功能描述：改进的欧拉算法求常微分方程组的初值问题
//输入参数：*y（ 指向函数初值以及函数返回值的指针n*(m+1)）
//          n（方程组个数），f（目标函数的计算）
//          h（步长），m（步数），a（区间起点）
//返回值：0（失败），1（成功）
=========================================================*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int euleradv(y, n, f, h, m, a)
double* y, (*f)(), h, a;
int n, m;
{
    double* y1, *y2, x;
    int k = 0, i;
    y1 = (double*)malloc(sizeof(double) * n); /* 微分方程预报值*/
    y2 = (double*)malloc(sizeof(double) * n);

    if (y1 == NULL || y2 == NULL) {
        printf("memory alloc failed.\n");
        return (0);
    }

    do {
        x = a + k * h;
        f(&y[k * n], y1, x);               /* 预报*/

        for (i = 0; i < n; i++) {
            y1[i] = y[k * n + i] + h * y1[i];
        }

        f(y1, y2, x + h);                  /* 再预报*/

        for (i = 0; i < n; i++) {
            y2[i] = y[k * n + i] + h * y2[i];
        }

        for (i = 0; i < n; i++) {
            y[(k + 1)*n + i] = (y1[i] + y2[i]) / 2;    /* 计算此处的函数值*/
        }

        k++;
    } while (k < m);

    free(y1);
    free(y2);
    return (1);
}
