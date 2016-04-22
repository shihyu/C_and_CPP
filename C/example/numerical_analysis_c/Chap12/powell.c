/*======================================================
// 函数名：powell
// 功能描述：powell方法求极值
// 输入参数：x[n] 输入搜索的出发点
//           ee[n*n] n组搜索的方向，每行为一个方向
//           xmin[n] 返回找到的最优点
//           y0      求得的极小值
//           n 初始区间的另一个端点
//           f 多元函数指针
//           eps 精度限度
//           itmax 最大迭代次数
// 返回值：  迭代次数
=========================================================*/
#include "stdlib.h"
#include "math.h"
#include "dirmin.c"

int powell(x, ee, xmin, n, y0, f, eps, itmax)
double* x, *ee, *xmin, *y0, eps;
double (*f)();
int n, itmax;
{
    int i, j, it, kk;
    double x0[21], x1[21], e[21];
    double y1, ymax, del, tmp;

    if (n > 20) {                                     /* 我们处理n<＝20的情况*/
        printf("you'd better simplify the problem\n");
        return (0);
    }

    *y0 = (*f)(x, n);                                 /* 初始的函数值*/
    it = 0;                                           /* 迭代次数为0*/

    for (i = 0; i < n; i++) {
        xmin[i] = x[i];
    }

    while (it++ < itmax) {
        for (i = 0; i < n; i++) {                     /* 记录下初始点x*/
            x0[i] = xmin[i];
        }

        ymax = *y0;
        kk = 0;
        del = 0.0;

        for (i = 0; i < n; i++) {                     /* 沿n个方向进行一维搜索*/
            for (j = 0; j < n; j++) {                 /* 第i个搜索方向*/
                e[j] = ee[i * n + j];
            }

            y1 = *y0;
            *y0 = dirmin(xmin, e, xmin, n, f, eps, itmax);  /* 从x出发，到更好的x*/

            if (y1 - *y0 > del) {                     /* 下降量*/
                del = y1 - *y0;
                kk = i;
            }
        }

        if (2.0 * (ymax - (*y0)) <= eps * (fabs(ymax) + fabs(*y0)) + 1.0e-25) {
            return (it);    /* 求得了最优解*/
        }

        for (i = 0; i < n; i++) {                    /* 外延*/
            x1[i] = 2.0 * xmin[i] - x0[i];
            e[i] = xmin[i] - x0[i];
        }

        y1 = (*f)(x1, n);                            /* 外延点的函数值*/

        if (y1 < ymax) {
            tmp = 2.0 * (ymax - 2.0 * (*y0) + y1) * (ymax - (*y0) - del) * (ymax -
                    (*y0) - del);
            tmp = tmp - del * (ymax - y1) * (ymax - y1);

            if (tmp < 0.0) {
                *y0 = dirmin(xmin, e, xmin, n, f, eps, itmax);

                for (j = 0; j < n; j++) {
                    ee[kk * n + j] = e[j];    /* 更新方向集体*/
                }
            }
        }
    }

    printf("exceeding maximum iterations\n");
    return (it);
}

