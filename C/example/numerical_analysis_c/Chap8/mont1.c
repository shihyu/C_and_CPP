#include "math.h"
#include "stdlib.h"
/*======================================================
// 函数名：mont1
// 功能描述：蒙特卡罗法求一元积分
// 输入参数：a 积分下限，b 积分上限,
//           f 指向被积函数的指针
// 返回值：  积分近似值
=========================================================*/
double mont1(a, b, f)
double a, b;
double (*f)();
{
    int k, n;
    double z, p, x;
    unsigned long r;            /* 随机数变量*/
    n = 5000;                  /* 产生5000个随机数*/
    z = 0.0;

    for (k = 0; k < n; k++) {
        r = rand();               /* 生成随机数*/
        p = (double)r / RAND_MAX;
        x = a + (b - a) * p;
        z = z + (*f)(x) / n;      /* 求和*/
    }

    z = z * (b - a);
    return (z);
}
