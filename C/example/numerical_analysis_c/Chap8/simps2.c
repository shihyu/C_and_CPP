#include "math.h"
#include "simps1.c"
/*======================================================
// 函数名：simps2
// 功能描述：变步长辛卜生求二重积分
// 输入参数：a 积分x下限, b 积分x上限,
//           n0 初始划分数
//           eps 精度要求
//           h0 x方向的最小步长
//           f 指向被积函数的指针
//           fy 指向计算y方向上下限的函数的指针
// 返回值：  积分近似值
=========================================================*/
double simps2(a, b, n0, eps, h0, f, fy)
double a, b, eps, h0;
int n0;
double (*f)();
void (*fy)();
{
    int n, k;
    double z, z2, s, s2, h, d, x, t1, t2;
    double g();
    n = n0;                            /* 初始的划分数*/
    h = (b - a) / n;                   /* 求得初始步长*/
    t1 = g(a, n0, eps, f, fy);
    t2 = g(b, n0, eps, f, fy);
    z = (t1 + t2) / 2.0;               /* 计算初始的积分值*/

    for (k = 1; k < n; k++) {
        x = a + k * h;                    /* 累次求和*/
        t1 = g(x, n0, eps, f, fy);
        z = z + t1;
    }

    z = z * h;                         /* 尽量减少乘法次数*/
    s = z;

    do {
        z2 = 0.0;

        for (k = 0; k < n; k++) {
            x = a + (k + 0.5) * h;         /* 累加计算*/
            t1 = g(x, n0, eps, f, fy);
            z2 = z2 + t1;
        }

        z2 = (z + h * z2) / 2.0;
        s2 = (4.0 * z2 - z) / 3.0;       /* 计算新的积分值*/
        d = fabs(s2 - s);                /* 计算两次积分值的差*/
        z = z2;
        s = s2;                          /* 更新积分值*/
        h = h / 2.0;                     /* 更新步长*/
        n = 2 * n;                       /* 更新划分数*/
    } while ((d > eps) && (h > h0));

    return (s);
}

static double g(t, n0, eps, f, fy) /* 子函数用于计算一维积分*/
double t, eps;
int n0;
double (*f)();
void (*fy)();
{
    int n, k;
    double y[2], a, b;                 /* 存放积分上限和下限*/
    double z, z2, s, s2, h, d, x;
    (*fy)(t, y);                       /* 计算上下限*/
    a = y[0];
    b = y[1];
    n = n0;                            /* 初始的划分数*/
    h = (b - a) / n;                   /* 求得初始步长*/
    z = ((*f)(t, a) + (*f)(t, b)) / 2.0; /* 计算初始的积分值*/

    for (k = 1; k < n; k++) {
        x = a + k * h;
        z = z + (*f)(t, x);                /* 累次求和*/
    }

    z = z * h;                         /* 尽量减少乘法次数*/
    s = z;

    do {
        z2 = 0.0;

        for (k = 0; k < n; k++) {
            x = a + (k + 0.5) * h;         /* 累加计算*/
            z2 = z2 + (*f)(t, x);
        }

        z2 = (z + h * z2) / 2.0;
        s2 = (4.0 * z2 - z) / 3.0;       /* 计算新的积分值*/
        d = fabs(s2 - s);                /* 计算两次积分值的差*/
        z = z2;
        s = s2;                          /* 更新积分值*/
        h = h / 2.0;                     /* 更新步长*/
        n = 2 * n;                       /* 更新划分数*/
    } while ((d > eps) && (n < 1000));  /* 这里改用最多区间数做限定*/

    return (s);
}
