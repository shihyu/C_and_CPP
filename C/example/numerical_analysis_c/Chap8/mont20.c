#include "math.h"
#include "stdio.h"
#include "simps2.c"
#include "mont2.c"
main()
{
    double a, b, eps, s, h0, f(double, double);
    void  fy(double, double []);
    a = 0.0;
    b = 4.0;
    eps = 0.0001;
    h0 = 1e-6;
    s = simps2(a, b, 10, eps, h0, f, fy);  /* 调用辛卜生积分法进行积分*/
    printf("simps2: s=%2.5f\n", s);        /* 打印积分结果*/
    s = mont2(a, b, a, b, f);              /* 调用蒙特卡洛积分法进行积分*/
    printf("mont2: s=%2.5f\n", s);        /* 打印积分结果*/
    getchar();
}
double f(x, y)                           /* 被积分的函数*/
double x, y;
{
    double z;
    z = exp(-x * y) / (1.0 + x * y);
    return (z);
}
void fy(x, y)                            /* 求积分界的函数*/
double x, y[2];
{
    y[0] = 0;
    y[1] = 4.0;
    return;
}
