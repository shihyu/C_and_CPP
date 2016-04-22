/*======================================================
//函数名：r_mqr
//功能描述：矩阵的QR分解
//输入参数：mat 指向待分解的矩阵的指针，返回是存放矩阵R
            m,n 矩阵阶数
            q   指向返回Q矩阵的指针
            eps 精度要求，小于此值的数据认为是0
//返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int r_mqr(mat, m, n, q, eps)
double* mat, *q, eps;
int m, n;
{
    int i, j, k, l, p;
    double u, alpha, t;

    if ((mat == NULL) || (q == NULL)) {        /* 检测指针是否为空*/
        printf("The matrix pointer is NULL\n");
        return (0);
    }

    if (m < n) {                               /* 要求矩阵维数必须满足m>n*/
        printf("Fail\n");
        return (0);
    }

    for (i = 0; i < m; i++) {                  /* Q矩阵赋初值成单位阵*/
        for (j = 0; j < m; j++) {
            q[i * m + j] = 0.0;
        }

        q[i * m + i] = 1.0;
    }

    for (k = 0; k < n; k++) {                  /* 循环做Householder变换*/
        u = 0.0;
        l = k * n + k;

        for (i = k; i < m; i++) {                /* 选取最大的值做it值，使计算稳定*/
            t = fabs(mat[i * n + k]);

            if (t > u) {
                u = t;
            }
        }

        alpha = 0.0;                             /* 计算alpha的值*/

        for (i = k; i < m; i++) {
            t = mat[i * n + k] / u;
            alpha = alpha + t * t;
        }

        if (alpha < eps) {                       /* 判断alpha值是否近似为0*/
            printf("Fail\n");                      /* 若alpha值过小，则计算终止*/
            return (0);
        }

        t = mat[l];

        if (t > 0.0) {
            u = -u;
        }

        alpha = u * sqrt(alpha);                 /* 完成alpha值的计算*/
        u = sqrt(2.0 * alpha * (alpha - t));     /* 计算rou值*/

        if (u > eps) {                           /* 判断rou值是否近似为0*/
            mat[l] = (t - alpha) / u;              /* 计算出的uk存放在原矩阵的空间中*/

            for (i = k + 1; i < m; i++) {          /* 计算出的ui存放在原矩阵的空间中*/
                p = i * n + k;
                mat[p] = mat[p] / u;
            }

            for (j = 0; j < m; j++) {              /* Hk 左乘 Q*/
                t = 0.0;

                for (l = k; l < m; l++) {
                    t = t + mat[l * n + k] * q[l * m + j];
                }

                for (i = k; i < m; i++) {
                    p = i * m + j;
                    q[p] = q[p] - 2.0 * t * mat[i * n + k];
                }
            }

            for (j = k + 1; j < n; j++) {          /* Hk 左乘原矩阵 A*/
                t = 0.0;

                for (l = k; l < m; l++) {
                    t = t + mat[l * n + k] * mat[l * n + j];
                }

                for (i = k; i < m; i++) {
                    p = i * n + j;
                    mat[p] = mat[p] - 2.0 * t * mat[i * n + k];
                }
            }

            mat[k * n + k] = alpha;

            for (i = k + 1; i < m; i++) {          /* 将矩阵A的第k列下三角部分置为0*/
                mat[i * n + k] = 0.0;
            }
        }
    }

    for (i = 0; i < m - 1; i++)                /* 转置得到矩阵Q*/
        for (j = i + 1; j < m; j++) {
            p = i * m + j;
            l = j * m + i;
            t = q[p];
            q[p] = q[l];
            q[l] = t;
        }

    return (1);
}