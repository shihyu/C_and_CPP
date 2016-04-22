#include "math.h"
#include "stdlib.h"
/*======================================================
// 函数名：mont2
// 功能描述：蒙特卡罗法求二重积分
// 输入参数：x0 x方向积分下限，x1 x方向积分上限,
//           y0 y方向积分下限，y1 y方向积分上限,
//           f 指向被积函数的指针
// 返回值：  积分近似值
=========================================================*/
double mont2(x0, x1, y0, y1, f)
double x0, x1, y0, y1;
double (*f)();
{
    int k, n;
    double z, p, x, y;
    unsigned long r;            /* 随机数变量*/
    n = 1000;                  /* 产生1000组随机数*/
    z = 0.0;

    for (k = 0; k < n; k++) {
        r = rand();               /* 生成随机数*/
        p = (double)r / RAND_MAX;
        x = x0 + (x1 - x0) * p;
        r = rand();
        p = (double)r / RAND_MAX;
        y = y0 + (y1 - y0) * p;
        z = z + (*f)(x, y) / n;     /* 求和*/
    }

    z = z * (y1 - y0) * (x1 - x0);
    return (z);
}
