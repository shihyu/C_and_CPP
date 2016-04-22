/*======================================================
// 函数名：cggm1
// 功能描述：共轭梯度法求极值，Fletcher-Reeves形式
// 输入参数：x[n] 输入搜索的出发点
//           xmin[n] 返回找到的最优点
//           y0      求得的极小值
//           n 初始区间的另一个端点
//           f 多元函数指针
//           df 多元函数的导函数的指针
//           eps 精度限度
//           itmax 最大迭代次数
// 返回值：  迭代次数
=========================================================*/
#include "stdlib.h"
#include "math.h"

int cggm1(x, xmin, n, y0, f, df, eps, itmax)
double* x, *xmin, *y0, eps;
double (*f)();
void (*df)();
int n, itmax;
{
    int i, it, flag;
    double g0[21], h[21];
    double y1, gg0, gg1, v, tiny;

    if (n > 20) {                                     /* 我们处理n<＝20的情况*/
        printf("you'd better simplify the problem\n");
        return (0);
    }

    for (i = 0; i < n; i++) {
        xmin[i] = x[i];
    }

    *y0 = (*f)(xmin, n);                              /* 计算函数值*/
    (*df)(xmin, g0, n);                               /* 计算梯度*/
    gg0 = 0.0;

    for (i = 0; i < n; i++) {
        g0[i] = -g0[i];
        h[i] = g0[i];
        gg0 = g0[i] * g0[i];
    }

    it = 0;
    flag = 0;
    tiny = n * 1.0e-20;

    while (it++ < itmax) {
        if (gg0 < tiny) {                                /* 已达到极小值*/
            return (it);
        }

        y1 = dirmin(xmin, h, xmin, n, f, eps, itmax);     /* 从x出发，到更好的x*/

        if (2.0 * (*y0 - y1) <= eps * (fabs(*y0) + fabs(y1) + 1.0e-25)) {
            *y0 = y1;
            flag++;

            if (flag == 3) {                              /* 连续三次函数值无变化，退出*/
                return (it);
            }
        } else {
            flag = 0;    /* flag置为0*/
        }

        *y0 = y1;
        (*df)(xmin, g0, n);                              /* 计算新点上的偏导*/
        gg1 = 0.0;

        for (i = 0; i < n; i++) {
            gg1 = gg1 + g0[i] * g0[i];
        }

        v = gg1 / gg0;

        if (v < 1.0e-25) {
            return (it);
        }

        for (i = 0; i < n; i++) {                        /* 计算新的h*/
            h[i] = -g0[i] + v * h[i];
            gg0 = gg1;
        }
    }

    printf("exceeding maximum iterations\n");
    return (it);
}
