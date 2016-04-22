/*======================================================
用插值法求非线性方程组的实根的实例
=========================================================*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include "interroot.c"

void main()
{
    double x, eps, ab;
    double f(double);
    double* x0 = &x;
    int max;
    *x0 = 1.0;                           /* 初值，精度，最大迭代次数*/
    ab = 0.0;
    eps = 0.00001;
    max = 60;
    printf("  x(k)         x(k+1)        dis\n");

    if (interroot(x0, ab, f, eps, max)) {
        printf("\n%1.7f\n", *x0);
    } else {
        printf("failed!\n");
    }
}

double f(x)                              /* 计算函数值*/
double x;
{
    return x * x * x - 3 * x + 1;
}
