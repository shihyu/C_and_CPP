/*======================================================
// 函数名：simplex
// 功能描述： 求线性规划问题的单纯形法
// 输入参数：n   问题的维数
//           m1  第一类约束条件的个数
//           m2  第二类约束条件的个数
//           m3  等式约束条件的个数
//           a[(m+2)*(n+1)] 单纯形表的存放空间，前m+1行是输入参数。
//                          函数结束时，返回单纯形表的最终结果
//           ixr[n] 单纯形表第一行的x标号
//           ixc[m] 单纯形表第一列的x标号
//           eps  精度要求，一般为1.0e-6
// 返回值：  若求解成功，则返回0。若无有限解，则返回1。若无可行解，则返回-1
=========================================================*/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define TINY 1.0e-7

int simplex(a, n, m1, m2, m3, ixr, ixc, eps)
int n, m1, m2, m3, *ixr, *ixc;
double* a, eps;
{
    int i, j, k, m, mp, np, ip, jp, flag;
    int lisx[101], lism2[101], nl1;
    int cmax1(), cmax2(), pivot();
    void mswap();
    double tmp, cmax;

    m = m1 + m2 + m3;

    if (n > 100) {
        printf("n should less than 100\n");
        return (-1);
    }

    mp = m + 2;
    np = n + 1;                                  /* 单纯表的规模*/

    for (i = 0; i <= m; i++) {
        if (a[i * np] < 0.0) {                   /* 第一列要求全部非负*/
            printf("negative B%d found\n", i);
            return (-1);
        }

        ixc[i] = n + i;                                  /* 左手变量编号n+1~n+m*/
    }

    for (k = 0; k <= n; k++) {                               /* 右手变量编号1~n*/
        lisx[k] = k;
        ixr[k] = k;
    }

    nl1 = n;

    if (m2 + m3 > 0) {                                        /* 需要解辅助问题*/
        for (i = 0; i <= m2; i++) {
            lism2[i] = 1;    /* m2类型的移动记录*/
        }

        for (j = 0; j < np;
             j++) {                            /* 计算辅助问题，各列求和*/
            tmp = 0.0;

            for (i = m1 + 1; i <= m; i++) {
                tmp = tmp + a[i * np + j];
            }

            a[(m + 1)*np + j] = -tmp;                         /* 求和结果存放在最后一行*/
        }

        flag = 1;

        while (flag == 1) {
            jp = cmax1(a, mp, np, m + 1, lisx, nl1, &cmax);    /* 找最后一行中的系数最大值*/

            if (cmax <= eps && a[(m + 1)*np] < -eps) {
                /* 系数都是正的，而且此时的极小值也小于0*/
                printf("no feasible solution.\n");             /* 无可行解*/
                return (-1);
            } else if (cmax <= eps && a[(m + 1)*np] <= eps) {
                /* 已经找到辅助问题的最优解，要交换参数z*/
                for (ip = m1 + m2 + 1; ip <= m; ip++) {
                    if (ixc[ip] == ip + n) {                   /* 找到一个参数z*/
                        /* 在本行找一个系数绝对值最大的，进行换元*/
                        jp = cmax2(a, mp, np, ip, lisx, nl1, &cmax);

                        if (fabs(cmax) > eps) {
                            mswap(a, mp, np, ip, jp);

                            for (j = 1; j <= nl1; j++)
                                if (lisx[j] == jp) {
                                    break;
                                }

                            nl1--;                           /* 这一列以后不再关心*/

                            for (k = j; k <= nl1; k++) {
                                lisx[k] = lisx[k + 1];
                            }

                            i = ixr[jp];              /* 更新左手变量和右手变量序列*/
                            ixr[jp] = ixc[ip];
                            ixc[ip] = i;
                        }
                    }
                }

                for (i = 1; i <= m2; i++) { /* 将m2形变量交换到前面，代替z，同时本行要取负号*/
                    if (lism2[i] == 1) {
                        k = (i + m1) * np;

                        for (j = 0; j < np; j++) {            /* 各个系数取负号*/
                            a[k + j] = -a[k + j];
                        }

                        a[k] = 0;
                    }
                }

                flag = 0;                                      /* 开始第二阶段*/
            } else {
                ip = pivot(a, mp, np, m, n, jp);                   /* 选主元*/

                if (ip == 0) {                                     /* 无可行解*/
                    printf("no feasible solution.\n");
                    return (-1);
                }

                mswap(a, mp, np, ip, jp);             /* 交换第ip行和第jp列对应的变量*/

                if (ixc[ip] > n + m1 + m2) {         /* 交换到一个z，且不是m2型的条件*/
                    for (j = 1; j <= nl1; j++)
                        if (lisx[j] == jp) {
                            break;
                        }

                    nl1--;                           /* 这一列以后不再关心*/

                    for (k = j; k <= nl1; k++) {
                        lisx[k] = lisx[k + 1];
                    }
                } else if (ixc[ip] > n + m1) {           /* 交换到一个z，但是是m2型的条件*/
                    i = ixc[ip] - n - m1;

                    if (lism2[i] == 1) {       /* 其实上是将x(n+m1+i)对应的列交换到第jp列*/
                        /* 也就是用这个x替换z*/
                        lism2[i] = 0;
                        a[(m + 1)*np + jp]++;

                        for (i = 0; i < mp; i++) {
                            a[i * np + jp] = -a[i * np + jp];
                        }
                    }
                }

                i = ixr[jp];                             /* 更新左手变量和右手变量序列*/
                ixr[jp] = ixc[ip];
                ixc[ip] = i;
            }
        }
    }

    while (1) {
        jp = cmax1(a, mp, np, 0, lisx, nl1, &cmax);    /* 查找最大值*/

        if (cmax < eps) {
            return (0);    /* 已经找到最优解*/
        }

        ip = pivot(a, mp, np, m, n, jp);               /* 选主元*/

        if (ip == 0) {
            return (1);    /* 没有有限解*/
        }

        mswap(a, mp, np, ip, jp);                      /* 交换*/
        i = ixr[jp];                             /* 更新左手变量和右手变量序列*/
        ixr[jp] = ixc[ip];
        ixc[ip] = i;
    }
}

int cmax1(a, mp, np, mm, ll, nll,
          cmax) /* 计算数组a中第mm行数组ll中各列中的最大元素cmax*/
double* a, *cmax;                                 /* 返回此最大元素的列号*/
int mp, np, mm, *ll, nll;                         /* mp,np是二维数组a的规模*/
{
    int kp, k;
    double tmp;
    kp = ll[1];
    *cmax = a[mm * np + kp];

    for (k = 2; k <= nll; k++) {                  /* 比较*/
        tmp = a[mm * np + ll[k]];

        if (tmp > *cmax) {
            *cmax = tmp;
            kp = ll[k];
        }
    }

    return (kp);
}

#include "math.h"                 /* 计算数组a中第mm行数组ll中各列中的绝对值最大的元素cmax*/
int cmax2(a, mp, np, mm, ll, nll, cmax)
double* a, *cmax;                                 /* 返回此最大元素的列号*/
int mp, np, mm, *ll, nll;                         /* mp,np是二维数组a的规模*/
{
    int kp, k;
    double tmp;
    kp = ll[1];
    *cmax = fabs(a[mm * np + kp]);

    for (k = 2; k <= nll; k++) {                 /* 比较绝对值*/
        tmp = fabs(a[mm * np + ll[k]]);

        if (tmp > *cmax) {
            *cmax = tmp;
            kp = ll[k];
        }
    }

    *cmax = a[mm * np + kp];
    return (kp);
}

int pivot(a, mp, np, m, n, kp)                  /* 选主元，考虑到表退化的情况*/
double* a;
int mp, np, m, n, kp;
{
    int ip, i, k;
    double p0, p1, p2, p3, tmp1, tmp2;
    ip = 0;

    for (i = 1; i <= m; i++)                    /* 查找是否有负元素*/
        if (a[i * np + kp] < -TINY) {
            break;
        }

    if (i > m) {
        return (ip);
    }

    p0 = -a[i * np] / a[i * np + kp];           /* 第一个负元素*/
    ip = i;

    for (i = ip + 1; i <= m; i++) {
        if (a[i * np + kp] < -TINY) {           /* 又一个负元素*/
            p1 =  -a[i * np] / a[i * np + kp];

            if (p1 < p0) {
                ip = i;
                p0 = p1;
            } else if (p1 == p0) {              /* 退化了*/
                tmp1 = 1.0 / (a[ip * np + kp]);
                tmp2 = 1.0 / (a[i * np + kp]);

                for (k = 1; k <= n; k++) {
                    p2 = -a[ip * np + k] * tmp1;
                    p3 = -a[i * np + k] * tmp2;

                    if (p2 != p3) {
                        break;
                    }
                }

                if (p3 < p2) {                   /* 选择较小的一个*/
                    ip = i;
                }
            }
        }
    }

    return (ip);
}

void mswap(a, mp, np, ip,
           kp)                        /* 换元，ip指定的行和kp指定列*/
double* a;
int mp, np, ip, kp;
{
    int i, k;
    double tmp;
    tmp = 1.0 / a[ip * np + kp];

    for (i = 0; i < ip; i++) {                        /* 先变换第ip行之外的行*/
        a[i * np + kp] = a[i * np + kp] * tmp;

        for (k = 0; k < kp; k++) {
            a[i * np + k] = a[i * np + k] - a[ip * np + k] * a[i * np + kp];
        }

        for (k = kp + 1; k < np; k++) {
            a[i * np + k] = a[i * np + k] - a[ip * np + k] * a[i * np + kp];
        }
    }

    for (i = ip + 1; i < mp; i++) {
        a[i * np + kp] = a[i * np + kp] * tmp;

        for (k = 0; k < kp; k++) {
            a[i * np + k] = a[i * np + k] - a[ip * np + k] * a[i * np + kp];
        }

        for (k = kp + 1; k < np; k++) {
            a[i * np + k] = a[i * np + k] - a[ip * np + k] * a[i * np + kp];
        }
    }

    a[ip * np + kp] = a[ip * np + kp] * tmp;             /* 变换第ip行*/
    tmp = -tmp;

    for (k = 0; k < kp; k++) {
        a[ip * np + k] *= tmp;
    }

    for (k = kp + 1; k < np; k++) {
        a[ip * np + k] *= tmp;
    }
}