#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"aitkenroot.c"

void main()
{
    double x, eps;
    double* x0 = &x;
    double f(double);
    int max;
    *x0 = 1.0;                            /* 初值，精度，最大迭代次数*/
    eps = 0.00001;
    max = 60;
    printf("  x(k)         x(k+1)        dis\n");

    if (aitkenroot(x0, f, eps, max)) {    /* 调用函数求解并打印结果*/
        printf("\n%1.5f\n\n", *x0);
    } else {
        printf("failed!\n");
    }

}

double f(x)                                 /* 计算函数值*/
double x;
{
    return  x * x * x - 2 * x + 1;
}