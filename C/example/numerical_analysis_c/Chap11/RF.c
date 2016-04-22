/*=============================================================
// 函 数 名：RF
// 功能描述：求解第一类椭圆积分的值
// 输入参数：x 求值的自变量
//           y 求值的自变量
//           z 求值的自变量
// 返 回 值：第一类椭圆积分的值
//==============================================================*/
#include "math.h"
double RF(x, y, z)
double x, y, z;
{
    double ll, t, t1, t2, flag, eps;
    double xt, yt, zt;
    eps = 1.0e-30;

    if (x < 0 || y < 0 || z < 0 || (x + y) < eps || (y + z) < eps ||
        (x + z) < eps) {       /* 检查自变量范围*/
        printf("Parameters incorrect\n");
        return (0.0);
    }

    do {
        t = sqrt(x);
        t1 = sqrt(y);
        t2 = sqrt(z);
        ll = t * (t1 + t2) + t1 * t2;
        x = (x + ll) / 4.0;                                    /* 更新x,y,z*/
        y = (y + ll) / 4.0;
        z = (z + ll) / 4.0;
        t = (x + y + z) / 3.0;
        xt = 1.0 - x / t;
        yt = 1.0 - y / t;
        zt = 1.0 - z / t;
        flag = fabs(zt) > fabs(yt) ? fabs(zt) : fabs(yt);
        flag = flag > fabs(xt) ? flag : fabs(xt);
    } while (flag >
             0.0025);                                 /* 这个阈值用于判断xyz充分接近*/

    t1 = xt * yt - zt *
         zt;                                  /* 用泰勒展开计算积分值*/
    t2 = xt * yt * zt;
    t = (1 - t1 / 10.0 + t2 / 14.0 + t1 * t1 / 24.0 - 3 * t1 * t2 / 44.0) / sqrt(t);
    return (t);
}
