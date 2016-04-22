#include "math.h"
/*======================================================
// 函数名：tzi2
// 功能描述：自适应梯形求积分
// 输入参数：a 积分下限，b 积分上限,
//           n0 初始划分数
//           eps 精度要求
//           h0 最小步长
//           f 指向被积函数的指针
// 返回值：  积分近似值
=========================================================*/
double tzi2(a, b, n0, eps, h0, f)
double a, b, eps, h0;
int n0;
double (*f)();
{
    int n, k;
    double z, h, t;
    double x0, x1, y0, y1;
    double subtz();
    n = n0;                                  /* 初始的划分数*/
    h = (b - a) / n;                         /* 求得初始步长*/
    z = 0.0;

    for (k = 0; k < n; k++) {
        x0 = a + k * h;                        /* 计算这个区间的两个端点*/
        x1 = a + (k + 1) * h;
        y0 = (*f)(x0);                         /* 计算这个区间两端的函数值*/
        y1 = (*f)(x1);
        t =  h * (y0 + y1) / 2.0;              /* 求得这个区间上的积分近似值*/
        t = subtz(x0, x1, y0, y1, h, t, eps / n, h0,
                  f); /* 调用子函数计算区间上的积分近似值*/
        z = z + t;
    }

    return (z);
}

static double subtz(x0, x1, y0, y1, h, t, eps, h0, f)
double x0, x1, y0, y1, h, t;
double eps, h0;
double (*f)();
{
    double x, y, t1, t2, d, z;
    x = x0 + h / 2.0;                        /* 区间的中点*/
    y = (*f)(x);                             /* 区间中点的函数值*/
    t1 = h * (y0 + y) / 4.0;
    t2 = h * (y + y1) / 4.0;                 /* 两个子区间的积分近似值*/
    d = fabs(t - (t1 + t2));

    if ((d < eps) || (h > h0)) {
        z = t1 + t2;    /* 已经满足精度要求或不允许继续划分*/
    } else {
        t1 = subtz(x0, x, y0, y, h / 2.0, t1, eps / 2.0, h0, f);
        t2 = subtz(x, x1, y, y1, h / 2.0, t2, eps / 2.0, h0, f);
        z = t1 + t2;                           /* 返回两个子区间的积分近似值之和*/
    }

    return (z);
}
