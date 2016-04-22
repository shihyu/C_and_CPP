/*======================================================
// 函数名：bfgs
// 功能描述：BFGS准牛顿法
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
#include "dirmin.c"

int bfgs(x, xmin, n, y0, f, df, eps, itmax)
double* x, *xmin, *y0, eps;
double (*f)();
void (*df)();
int n, itmax;
{
    int i, j, it, flag;
    double H[41][41], g0[41], dg[41], dx[41], hdg[41];
    double y1, tiny, pq1, uij,  pq, qhq, qhq1;

    if (n > 40) {                                     /* 我们处理n<＝20的情况*/
        printf("you'd better simplify the problem\n");
        return (0);
    }

    for (i = 0; i < n; i++) {
        xmin[i] = x[i];
    }

    *y0 = (*f)(xmin, n);                              /* 计算函数值*/
    (*df)(xmin, g0, n);                               /* 计算梯度*/

    for (i = 0; i < n; i++) {
        dx[i] = -g0[i];                               /* 初始的搜索方向*/

        for (j = 0; j < n; j++) {                     /* H的初值设为n阶单位阵*/
            H[i][j] = 0.0;
        }

        H[i][i] = 1.0;
    }

    it = 0;
    flag = 0;
    tiny = n * 1.0e-20;

    while (it++ < itmax) {
        y1 = dirmin(xmin, dx, xmin, n, f, eps, itmax);    /* 从x出发，到更好的x. p=dx*/

        if (2.0 * (*y0 - y1) <= eps * (fabs(*y0) + fabs(y1) + tiny)) {
            *y0 = y1;
            flag++;

            if (flag == 3) {                              /* 连续三次函数值无变化，退出*/
                return (it);
            }
        } else {
            flag = 0;    /* flag置为0*/
        }

        *y0 = y1;

        for (i = 0; i < n; i++) {
            dg[i] = g0[i];    /* g0暂存在dg中*/
        }

        (*df)(xmin, g0, n);                              /* 计算新点上的偏导*/

        for (i = 0; i < n; i++) {
            dg[i] = g0[i] - dg[i];    /* q = g1-g0*/
        }

        for (i = 0; i < n; i++) {
            hdg[i] = 0.0;

            for (j = 0; j < n; j++) {
                hdg[i] = hdg[i] + H[i][j] * dg[i];    /* H*q */
            }
        }

        pq = 0.0;
        qhq = 0.0;                                       /* 求pT*q 和qT*H*q */

        for (i = 0; i < n; i++) {
            pq = pq + dx[i] * dg[i];
            qhq = qhq + dg[i] * hdg[i];                  /* qT*H*q */
        }

        if (pq < tiny || qhq < tiny) {                   /* 已收敛*/
            return (it);
        }

        pq = 1.0 / pq;
        qhq1 = 1.0 / qhq;

        for (i = 0; i < n; i++) {
            dg[i] = pq * dx[i] - qhq1 * hdg[i];    /* u */
        }

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++) {                          /* 更新H矩阵*/
                pq1 = pq * dx[i] * dx[j] - qhq1 * hdg[i] * hdg[j];
                uij = qhq * dg[i] * dg[j];
                H[i][j] = H[i][j] + pq1 + uij;
            }

        for (i = 0; i < n; i++) {                         /* 求下次的搜索方向*/
            dx[i] = 0.0;

            for (j = 0; j < n; j++) {
                dx[i] = dx[i] - H[i][j] * g0[j];
            }
        }
    }

    printf("exceeding maximum iterations\n");
    return (it);
}
