#include "stdio.h"
#include "hemt.c"
#include "gasi.c"
main()
{
    double f1(double), z;
    printf("Hermite:\n");                      /* 埃尔米特-高斯求积法*/
    z = hemt(f1);
    printf("t=%2.8f\n", z);
    printf("Gauss:\n");                        /* 自适应高斯求积法*/
    z = gasi(-1.0e35, 1.0e35, 1.0e-9, 10, f1);
    printf("t=%2.8f\n", z);
}

double f1(x)                                  /* 被积函数*/
double x;
{
    double y;
    y = x * x * x * x * exp(-x * x);
    return (y);
}
