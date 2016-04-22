/*======================================================
//函数名：jcb1
//功能描述：对称矩阵求特征值
//输入参数：a   指向存放对称矩阵的指针
n   矩阵阶数
u   返回的特征值
eps 精度要求，用于判断元素是否为0
itmax 最大迭代次数
//返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
int jcb1(a, n, u, eps, itmax)
double* a, *u, eps;
int n, itmax;
{
    int i, j, p, q, it;
    double sint, cost, sin2t, cos2t, d, tmp, t1, t2, t3;
    it = 0;

    while (it < itmax) {
        it++;
        d = 0.0;

        for (i = 1; i < n; i++)             /* 寻找绝对值最大的元素*/
            for (j = 0; j < i; j++) {
                tmp = fabs(a[i * n + j]);

                if (tmp > d) {
                    d = tmp;
                    p = i;
                    q = j;
                }
            }

        if (d < eps) {                      /* 已经收敛成对角阵，此时迭代完成*/
            for (i = 0; i < n; i++) {       /* 取出特征值*/
                u[i] = a[i * n + i];
            }

            return (it);
        }

        sint = 2 * a[p * n + q];
        cost = a[q * n + q] - a[p * n + p];
        sin2t = sint / (sqrt(sint * sint + cost * cost));

        if (cost < 0.0) {
            sin2t = -sin2t;    /* 计算sin(2 theta)*/
        }

        cos2t = sqrt(1.0 - sin2t * sin2t);
        sint = sin2t / (sqrt(2 * (1.0 + cos2t))); /* 计算givens矩阵元素*/
        cost = sqrt(1.0 - sint * sint);
        tmp = a[p * n + p];               /* 相似变换*/
        t1 = tmp * cost * cost;
        t2 = a[q * n + q] * cost * cost;
        t3 = a[p * n + q] * sin2t;
        a[p * n + p] = t1 + a[q * n + q] - t2 - t3;
        a[q * n + q] = tmp - t1 + t2 + t3;
        a[p * n + q] = 0.0;
        a[q * n + p] = 0.0;

        for (j = 0; j < n; j++)          /* 第p行和第q行的变换*/
            if ((j != p) && (j != q)) {
                tmp = a[p * n + j];
                a[p * n + j] = tmp * cost - a[q * n + j] * sint;
                a[q * n + j] = tmp * sint + a[q * n + j] * cost;
            }

        for (i = 0; i <= n - 1; i++)    /* 用对称性可求得第p列和第q列*/
            if ((i != p) && (i != q)) {
                a[i * n + p] = a[p * n + i];
                a[i * n + q] = a[q * n + i];
            }
    }

    return (0);
}

