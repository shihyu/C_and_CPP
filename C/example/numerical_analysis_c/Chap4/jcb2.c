/*======================================================
//函数名：jcb2
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
int jcb2(a, n, u, eps, itmax)
double* a, *u, eps;
int n, itmax;
{
    int i, j, p, q, it, flag;
    double sint, cost, sin2t, cos2t, tmp, r, t1, t2, t3;
    r = 0.0;

    for (i = 1; i < n; i++)
        for (j = 0; j < i; j++) {
            r = r + a[i * n + j] * a[i * n + j];
        }

    r = 2.0 * r;                             /* 求出初始的r*/
    it = 0;

    while ((it < itmax) && (r > eps)) {
        it++;
        flag = 1;
        r = r / n;

        while (flag == 1) {
            p = 0;
            q = 0;

            for (i = 1; i < n; i++)             /* 寻找大于r的非对角线元素*/
                for (j = 0; j < i; j++) {
                    tmp = fabs(a[i * n + j]);

                    if (tmp > r) {
                        p = i;
                        q = j;
                        j = i;
                        i = n;              /* 找到第一个，终止扫描*/
                    }
                }

            if (p == 0) {                      /* 没有大于r的非对角线元素，此次扫描完成*/
                flag = 0;
            } else {
                sint = 2 * a[p * n + q];
                cost = a[q * n + q] - a[p * n + p];
                sin2t = sint / (sqrt(sint * sint + cost * cost)); /* 计算sin(2 theta)*/

                if (cost < 0.0) {
                    sin2t = -sin2t;
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
        }
    }

    for (i = 0; i < n; i++) {                       /* 计算特征值*/
        u[i] = a[i * n + i];
    }

    return (it < itmax);                            /* 若it<itmax，则说明迭代成功*/
}