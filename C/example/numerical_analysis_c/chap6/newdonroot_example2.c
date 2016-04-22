#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include "newdonroot.c"

void main()
{
    double x0;
    double f(double);
    double fd(double);
    double eps;
    int max;
    x0 = 0.0;                       /* 初值，精度，最大迭代次数*/
    eps = 0.00001;
    max = 60;
    printf("  x(k)         x(k+1)        dis\n\n");

    if (newdonroot(&x0, f, fd, eps, max)) {
        printf("\n%1.7f\n", x0);
    } else {
        printf("failed!\n");
    }
}

double f(x)                         /* 计算函数值*/
double x;
{
    return x * x * x - 3 * x + 1;
}

double fd(x)                        /* 计算导函数值*/
double x;
{
    return 3 * x * x - 3;
}
