/*=============================================================
// 函 数 名：beta
// 功能描述：求解贝塔函数的值
// 输入参数： x 函数变量
//            y 函数变量
// 返 回 值：贝塔函数的值
//==============================================================*/
#include "math.h"
double beta(x, y)
double x, y;
{
    double t;

    if ((x < 0) || (y < 0)) {                    /* 判断自变量是否满足要求*/
        printf("negative input parameter\n");
        return (0.0);
    }

    t = gammln(x) + gammln(y) - gammln(x + y);   /* 使用伽马函数实现*/
    t = exp(t);
    return (t);
}
