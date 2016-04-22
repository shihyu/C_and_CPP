/*======================================================
//函数名：smtr
//功能描述：矩阵相似变换为三对角矩阵
//输入参数：mat 指向待分解的矩阵的指针，返回时存放三对角阵
            n   矩阵阶数
            q   指向返回Q矩阵的指针
            eps 精度要求，小于此值的数据认为是0
//返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int smtr(mat, n, q, eps)
double* mat, *q, eps;
int n;
{
    int i, j, k, l, m, p;
    double u, alpha, t, *tmp;

    if ((mat == NULL) || (q == NULL)) { /* 检测指针是否为空*/
        printf("The matrix pointer is NULL\n");
        return (0);
    }

    tmp = (double*)malloc(n * sizeof(double)); /* 为临时变量分配空间*/

    for (i = 0; i < n; i++) {                  /* Q矩阵赋初值成单位阵*/
        for (j = 0; j < n; j++) {
            q[i * n + j] = 0.0;
        }

        q[i * n + i] = 1.0;
    }

    for (k = 0; k < n - 2; k++) {              /* 循环做Householder变换*/
        u = 0.0;
        l = (k + 1) * n + k;

        for (i = k + 1; i < n; i++) {            /* 选取最大的值做it值，使计算稳定*/
            t = fabs(mat[i * n + k]);

            if (t > u) {
                u = t;
            }
        }

        alpha = 0.0;                             /* 计算alpha的值*/

        for (i = k + 1; i < n; i++) {
            t = mat[i * n + k] / u;
            alpha = alpha + t * t;
        }

        if (alpha < eps) {                       /* 判断alpha值是否近似为0*/
            printf("Fail\n");                       /* 若alpha值过小，则计算终止*/
            free(tmp);
            return (0);
        }

        t = mat[l];

        if (t > 0.0) {
            u = -u;
        }

        alpha = u * sqrt(alpha);                 /* 完成alpha值的计算*/
        u = sqrt(2.0 * alpha * (alpha - t));       /* 计算rou值*/

        if (u > eps) {                          /* 判断rou值是否近似为0*/
            mat[l] = (t - alpha) / u;               /* 计算出的uk存放在原矩阵的空间中*/

            for (i = k + 2; i < n; i++) {          /* 计算出的ui存放在原矩阵的空间中*/
                p = i * n + k;
                mat[p] = mat[p] / u;
            }

            for (j = 0; j < n; j++) {              /* Hk 左乘 Q*/
                t = 0.0;

                for (l = k + 1; l < n; l++) {
                    t = t + mat[l * n + k] * q[l * n + j];
                }

                for (i = k + 1; i < n; i++) {
                    p = i * n + j;
                    q[p] = q[p] - 2.0 * t * mat[i * n + k];
                }
            }

            for (j = k + 1; j < n; j++) {          /* Hk 同时左乘和右乘原矩阵 A*/
                t = 0.0;

                for (l = k + 1; l < n; l++) {        /* 求出需要用到的各个ti*/
                    t = t + mat[l * n + k] * mat[l * n + j];
                }

                tmp[j] = t;
            }

            t = 0.0;

            for (m = k + 1; m < n; m++) {          /* 求出计算aij需要的求和部分*/
                t = t + tmp[m] * mat[m * n + k];
            }

            for (j = k + 1; j < n; j++)            /* 计算aij*/
                for (i = k + 1; i < j + 1; i++) {
                    p = i * n + j;
                    mat[p] = mat[p] - 2.0 * tmp[i] * mat[j * n + k]
                             - 2.0 * tmp[j] * mat[i * n + k] + 4.0 * mat[i * n + k] * t * mat[j * n + k];
                    mat[j * n + i] = mat[p];             /* 更新得的矩阵a是对称矩阵*/
                }

            mat[(k + 1)*n + k] = alpha;
            mat[k * n + k + 1] = alpha;

            for (i = k + 2; i < n; i++) {          /* 将矩阵A的第k列下三角部分置为0*/
                mat[i * n + k] = 0.0;
                mat[k * n + i] = 0.0;
            }
        }
    }

    for (i = 0; i < n - 1; i++)                 /* 转置得到矩阵Q*/
        for (j = i + 1; j < n; j++) {
            p = i * n + j;
            l = j * n + i;
            t = q[p];
            q[p] = q[l];
            q[l] = t;
        }

    free(tmp);
    return (1);
}

