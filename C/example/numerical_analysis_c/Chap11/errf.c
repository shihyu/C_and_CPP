/*=============================================================
// 函 数 名：errf
// 功能描述：求解误差函数的值
// 输入参数：x 自变量x的值。
// 返 回 值：误差函数的值
//==============================================================*/
#include "stdio.h"
#include "math.h"
#include "gamm2.c"
#define EPS 1.0e-6                    /* 使用不完全伽马函数需要的数据*/
#define DMIN 1.0e-30
double errf(x)
double x;
{
    double t;
    t = gamm2(0.5, x * x, EPS, DMIN);

    if (x < 0) {                        /* 若x<0，则取负*/
        t = -t;
    }

    return (t);
}
