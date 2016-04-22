/*======================================================
//函数名：mhdqr
//功能描述：上H矩阵求特征值
//输入参数：a   指向存放上H矩阵的指针
            n   矩阵阶数
            u   返回的特征值的实部
            v   返回的特征值的虚部
            eps 精度要求，用于判断元素是否为0
            itmax 最大迭代次数
//返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
int mhdqr(a, n, u, v, eps, itmax)
double* a, *u, *v, eps;
int n, itmax;
{
    int i, j, k, ii, jj, kk;
    double x, y, p, q, r;                      /* 用于进行相似变换*/
    double q00, q01, q02, q11, q12, q22;       /* 用于求Q*/
    int is1, is2, n1;                          /* 用于分解问题*/
    double* a1;                                /* 用于存放小规模的问题*/
    double b, c, s;                            /* 用于计算2阶矩阵的特征值*/

    if (itmax == 0) {                         /* 已经不能再迭代*/
        printf("fail\n");
        return (0);
    }

    if (n == 1) {                              /* 矩阵是1阶*/
        u[0] = a[0];
        v[0] = 0.0;
        return (1);
    }

    if (n == 2) {                             /* 矩阵是2阶*/
        b = (a[0] + a[3]);
        c = a[0] * a[3] - a[1] * a[2];
        s = b * b - 4.0 * c;
        y = sqrt(fabs(s));

        if (s > 0.0) {                         /* 两个特征值是实的*/
            if (b > 0.0) {
                u[0] = (b + y) / 2.0;
            } else {
                u[0] = (b - y) / 2.0;
            }

            v[0] = 0.0;
            u[1] = c / u[0];
            v[1] = 0.0;
        } else {                               /* 两个特征值是复共轭的*/
            u[0] = b / 2.0;
            v[0] = y / 2.0;
            u[1] = u[0];
            v[1] = -v[0];
        }

        return (1);
    }

    is1 = 0;
    is2 = 0;

    while (is2 < n - 1) {                      /* 分割成小规模问题*/
        is2++;
        j = is2 * n + is2;

        if (fabs(a[j - 1]) < eps * (fabs(a[j - n - 1]) + fabs(
                                        a[j]))) { /* 寻找次对角线上0元素*/
            n1 = is2 - is1;
            printf("Partion: is1=%d,is2=%d,size=%d\n", is1, is2, n1);
            a1 = (double*)malloc(n1 * n1 * sizeof(double));

            for (i = 0; i < n1; i++)
                for (j = 0; j < n1; j++) {
                    a1[i * n1 + j] = a[(i + is1) * n + j + is1];
                }

            mhdqr(a1, n1, u + is1, v + is1, eps, itmax); /* 递归调用函数求解*/
            free(a1);
            is1 = is2;
        }
    }

    if (is1 > 0 &&
        is1 < n) {                    /* 进行过分割，且最后一块矩阵未求解*/
        n1 = n - is1;
        printf("Partion: is1=%d,is2=%d,size=%d\n", is1, n, n1);
        a1 = (double*)malloc(n1 * n1 * sizeof(double));

        for (i = 0; i < n1; i++)
            for (j = 0; j < n1; j++) {
                a1[i * n1 + j] = a[(i + is1) * n + j + is1];
            }

        mhdqr(a1, n1, u + is1, v + is1, eps, itmax); /* 递归调用函数求解最后一块矩阵*/
        free(a1);
        return (1);
    } else if (is1  == n) {
        return (1);
    }

    for (k = 0; k < n - 1; k++) {
        if (k == 0) {                            /* 处理第一列应用了位移策略*/
            x = a[(n - 2) * n + n - 2] + a[n * n - 1];
            y = a[(n - 2) * n + n - 2] * a[n * n - 1] - a[(n - 2) * n + n - 1] * a[(n - 1) *
                    n + n - 2];
            p = a[0] * (a[0] - x) + a[1] * a[n] + y;
            q = a[n] * (a[0] + a[n + 1] - x);
            r = a[n] * a[2 * n + 1];
        } else {                  /* 其余各列的运算就是要将矩阵恢复成上H矩阵*/
            p = a[k * n + k - 1];
            q = a[(k + 1) * n + k - 1];

            if (k != n - 2) {
                r = a[(k + 2) * n + k - 1];
            } else {
                r = 0.0;
            }
        }

        if ((fabs(p) + fabs(q) + fabs(r)) != 0.0) { /* 都是0，这一列就不需要处理*/
            if (p < 0.0) {                     /* 求Q*/
                s = -sqrt(p * p + q * q + r * r);
            } else {
                s = sqrt(p * p + q * q + r * r);
            }

            if (k != 0) {
                a[k * n + k - 1] = -s;
            }

            q00 = -p / s;                   /* Q的各个基本元素*/
            q01 = -q / s;
            q02 = -r / s;
            q11 = -q00 - q02 * r / (p + s);
            q12 = q01 * r / (p + s);
            q22 = -q00 - q01 * q / (p + s);

            if (k == n - 2) {               /* 当k为n-2时，只改变2行*/
                for (j = k; j < n; j++) {    /* Q左乘A，最多改变k,k+1,k+2这3行上的n-k列元素*/
                    ii = k * n + j;
                    jj = (k + 1) * n + j;
                    p = q00 * a[ii] + q01 * a[jj];
                    q = q01 * a[ii] + q11 * a[jj];
                    a[ii] = p;
                    a[jj] = q;
                }
            } else {
                for (j = k; j < n; j++) {    /* Q左乘A，最多改变k,k+1,k+2这3行上的n-k列元素*/
                    ii = k * n + j;
                    jj = (k + 1) * n + j;
                    kk = (k + 2) * n + j;
                    p = q00 * a[ii] + q01 * a[jj];
                    q = q01 * a[ii] + q11 * a[jj];
                    r = q02 * a[ii] + q12 * a[jj];
                    p = p + q02 * a[kk];
                    q = q + q12 * a[kk];
                    r = r + q22 * a[kk];
                    a[ii] = p;
                    a[jj] = q;
                    a[kk] = r;
                }
            }

            j = k + 3;                     /* 计算Q右乘A影响的行数，主要是边界问题*/

            if (j >= n - 1) {
                j = n - 1;
            }

            if (k == n - 2) {          /* 当k+2为n时，只影响2列*/
                for (i = 0; i <= j; i++) {    /* Q右乘A，最多影响3列，第k,k+1,k+2列*/
                    ii = i * n + k;
                    jj = i * n + k + 1;
                    p = q00 * a[ii] + q01 * a[jj];
                    q = q01 * a[ii] + q11 * a[jj];
                    a[ii] = p;
                    a[jj] = q;
                }
            } else {
                for (i = 0; i <= j; i++) {    /* Q右乘A，最多影响3列，第k,k+1,k+2列*/
                    ii = i * n + k;
                    jj = i * n + k + 1;
                    kk = i * n + k + 2;
                    p = q00 * a[ii] + q01 * a[jj];
                    q = q01 * a[ii] + q11 * a[jj];
                    r = q02 * a[ii] + q12 * a[jj];
                    kk = i * n + k + 2;
                    p = p + q02 * a[kk];
                    q = q + q12 * a[kk];
                    r = r + q22 * a[kk];
                    a[ii] = p;
                    a[jj] = q;
                    a[kk] = r;
                }
            }
        }

        if (k > 0) {                   /* 这两行元素是0*/
            a[(k + 1)*n + k - 1] = 0.0;

            if (k != n - 2) {
                a[(k + 2)*n + k - 1] = 0.0;
            }
        }
    }

    i = mhdqr(a, n, u, v, eps, itmax - 1); /* 进行完相似变换后再递归调用函数求解*/
    return (i);
}

