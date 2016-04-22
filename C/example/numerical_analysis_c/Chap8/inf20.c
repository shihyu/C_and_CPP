#include "stdio.h"
#include "lagr.c"
#include "gasi.c"
main()
{
    double  f1(), f2(), z;
    printf("Laguerre:\n");
    z = lagr(0.0, f1, 1);                    /* 拉盖尔-高斯求积法计算第一个积分*/
    printf("f1: t1=%2.8f\n", z);
    z = lagr(0.0, f2, -1);                   /* 拉盖尔-高斯求积法计算第二个积分*/
    printf("f2: t2=%2.8f\n", z);
    printf("Gauss\n");
    z = gasi(0.0, 1.0e35, 1.0e-9, 10, f1);   /* 自适应高斯求积法计算第一个积分*/
    printf("f1: t1=%2.8f\n", z);
    z = gasi(-1.0e35, 0.0, 1.0e-9, 10, f2);  /* 自适应高斯求积法计算第二个积分*/
    printf("f2: t2=%2.8f\n", z);
}

double f1(x)                               /* 被积函数1*/
double x;
{
    double y;
    y = x * x * exp(-x);
    return (y);
}
double f2(x)                               /* 被积函数2*/
double x;
{
    double y;
    y = x * x * exp(x);
    return (y);
}
