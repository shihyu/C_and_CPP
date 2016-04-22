/*=============================================================
// 函 数 名：RD
// 功能描述：求解第二类椭圆积分的值
// 输入参数：x 求值的自变量
//           y 求值的自变量
//           z 求值的自变量
// 返 回 值：第二类椭圆积分的值
//==============================================================*/
#include "math.h"
double RD(x, y, z)
double x, y, z;
{
    double ll, flag, eps, s, f;
    double t, t1, t2, t3, t4, t5, t6;
    double xt, yt, zt;
    eps = 1.0e-25;

    if (x < 0 || y < 0 || (x + y) < eps || z < eps) { /* 检查自变量范围*/
        printf("Parameters incorrect\n");
        return (0.0);
    }

    s = 0.0;
    f = 4.0;

    do {
        t1 = sqrt(x);
        t2 = sqrt(y);
        t3 = sqrt(z);
        ll = t1 * (t2 + t3) + t2 * t3;
        f = f / 4.0;
        s = s + f / (sqrt(z) * (z + ll));
        x = (x + ll) / 4.0;                                    /* 更新x,y,z*/
        y = (y + ll) / 4.0;
        z = (z + ll) / 4.0;
        t = (x + y + 3.0 * z) / 5.0;
        xt = 1.0 - x / t;
        yt = 1.0 - y / t;
        zt = 1.0 - z / t;
        flag = fabs(zt) > fabs(yt) ? fabs(zt) : fabs(yt);
        flag = flag > fabs(xt) ? flag : fabs(xt);
    } while (flag >
             0.0015);                                 /* 这个阈值用于判断xyz充分接近*/

    t1 = xt * yt;                                            /* 用泰勒展开计算积分值*/
    t2 = zt * zt;
    t3 = t1 - t2;
    t4 = t1 - 6.0 * t2;
    t5 = t4 + 2 * t3;
    t6 = zt;
    t = (1 + t4 * (-3.0 / 14.0 + 9.0 * t4 / 88.0 - 9.0 * t5 * t6 / 52.0) +
         t6 * (t5 / 5.0 + t6 * (-9.0 * t3 / 22.0 + 3 * t1 * t6 / 26.0))) / (t * sqrt(t));
    t = 3.0 * s + f * t;
    return (t);
}
