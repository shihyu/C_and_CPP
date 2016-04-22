#include "stdio.h"
#include "leg1.c"
#include "cheb.c"
#include "gasi.c"
main()
{
    double a, b, eps, h0, z;
    double f1(double);
    a = 0.0;
    b = 4.0;
    eps = 1e-8;
    h0 = 1e-5;
    z = leg1(a, b, 4, eps, h0, f1);              /* 用勒让德-高斯求积法积分*/
    printf("lagr: t=%7.6f\n", z);                /* 打印结果*/
    z = cheb(a, b, 4, eps, h0, f1);              /* 用切比雪夫求积法积分*/
    printf("cheb: t=%7.6f\n", z);
    z = gasi(a, b, eps, 10, f1);               /* 用自适应高斯求积法积分*/
    printf("gasi: t=%7.6f\n", z);
}

#include "math.h"
double f1(x)
double x;                                      /* 被积分的函数*/
{
    double y;
    y = exp(-x * x) / (1.0 + x * x);
    return (y);
}
