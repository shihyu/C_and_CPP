/*=============================================================
// 函 数 名：chii
// 功能描述：求解卡方分布函数的值
// 输入参数：x 自变量x的值。
//           n 整数
// 返 回 值：卡方分布函数的值
//==============================================================*/
#include "stdio.h"
#include "math.h"
#include "gamm2.c"
#define EPS 1.0e-6                    /* 使用不完全伽马函数需要的数据*/
#define DMIN 1.0e-30
double chii(x, n)
double x;
int n;
{
    double t;

    if (x < 0) {                        /* 若x<0，则不能计算*/
        printf("negative x\n");
        return (0.0);
    }

    t = gamm2(n / 2.0, x / 2.0, EPS, DMIN); /* 调用不完全伽马函数求值*/
    return (t);
}
