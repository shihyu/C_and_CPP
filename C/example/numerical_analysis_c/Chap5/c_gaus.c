/*======================================================
// 函数名：c_gaus
// 功能描述：用高斯消去法解线性方程组
// 输入参数：a 解系数矩阵，b 常数矩阵，x返回的解向量
//           n 未知数个数，eps 精度要求，小于eps的值，认为是0。
// 返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "c_comp.c"

int c_gaus(a, b, x, n, eps)
struct c_comp* a, *b, *x;
int n;
double eps;
{
    int i, j, k, l, v, exis, *exjs;
    struct c_comp c_tmp, c_tmp2;
    double tmp, d;

    if ((a == NULL) || (b == NULL) || (x == NULL)) { /* 检测输入的指针是否为空*/
        printf("The pointer exis NULL\n");
        return (0);
    }

    exjs = malloc(n * sizeof(int));        /* 为列交换记录分配空间并检测是否成功*/

    if (exjs == NULL) {
        printf("Memory alloc failed\n");
        return (0);
    }

    for (k = 0; k < n; k++) {
        d = 0.0;

        for (i = k; i < n; i++)                         /* 此循环用于选取主元*/
            for (j = k; j < n; j++) {
                l = i * n + j;
                tmp = a[l].rmz * a[l].rmz + a[l].imz * a[l].imz; /* 求元素的模*/

                if (tmp > d) {
                    d = tmp;
                    exis = i;
                    exjs[k] = j;
                }
            }

        if (d < eps) {                                  /* 判断主元是否过小*/
            free(exjs);
            printf("failed.\n");
            return (0);                                   /* 若主元过小则退出程序*/
        }

        if (exis != k) {                                  /* 判断是否需要行交换*/
            for (j = 0; j < n; j++) {                     /* 进行行交换*/
                l = k * n + j;
                v = exis * n + j;
                tmp = a[l].rmz;
                a[l].rmz = a[v].rmz;
                a[v].rmz = tmp;
                tmp = a[l].imz;
                a[l].imz = a[v].imz;
                a[v].imz = tmp;
            }

            tmp = b[k].rmz;                              /* 常数向量也要进行行交换*/
            b[k].rmz = b[exis].rmz;
            b[exis].rmz = tmp;
            tmp = b[k].imz;
            b[k].imz = b[exis].imz;
            b[exis].imz = tmp;
        }

        if (exjs[k] != k)                                /* 判断是否需要列交换*/
            for (i = 0; i < n; i++) {                    /* 进行列交换*/
                l = i * n + k;
                v = i * n + exjs[k];
                tmp = a[l].rmz;
                a[l].rmz = a[v].rmz;
                a[v].rmz = tmp;
                tmp = a[l].imz;
                a[l].imz = a[v].imz;
                a[v].imz = tmp;
            }

        l = k * n + k;                             /* 取共轭将复数除法转化为乘法*/
        a[l].rmz = a[l].rmz / d;
        a[l].imz = -a[l].imz / d;

        for (j = k + 1; j < n; j++) {  /* 归一化计算的第二步，需要使用复数的乘法*/
            v = k * n + j;
            c_comp_product(&a[v], &a[l], &a[v]);
        }

        c_comp_product(&b[k], &a[l], &b[k]);          /* 常数向量的归一化计算*/

        for (i = k + 1; i < n; i++) {                 /* 消元计算*/
            for (j = k + 1; j < n; j++) {
                c_comp_product(&a[i * n + k], &a[k * n + j], &c_tmp);
                a[i * n + j].rmz = a[i * n + j].rmz - c_tmp.rmz;
                a[i * n + j].imz = a[i * n + j].imz - c_tmp.imz;
            }

            c_comp_product(&a[i * n + k], &b[k], &c_tmp);
            b[i].rmz = b[i].rmz - c_tmp.rmz;           /* 常数向量也要进行消元计算*/
            b[i].imz = b[i].imz - c_tmp.imz;
        }
    }

    x[n - 1].rmz = b[n - 1].rmz;                   /* 第一个解可直接读出*/
    x[n - 1].imz = b[n - 1].imz;

    for (i = n - 2; i >= 0; i--) {                 /* 继续进行回代，求出解向量*/
        c_tmp.rmz = 0;
        c_tmp.imz = 0;

        for (j = i + 1; j < n; j++) {
            c_comp_product(&a[i * n + j], &x[j], &c_tmp2);
            c_comp_plus(&c_tmp2, &c_tmp, &c_tmp);
        }

        x[i].rmz = b[i].rmz - c_tmp.rmz;
        x[i].imz = b[i].imz - c_tmp.imz;
    }

    for (k = n - 1; k >= 0; k--) {             /* 依照列交换的历史进行结果恢复*/
        if (exjs[k] != k) {                        /* 判断是否需要恢复*/
            tmp = x[k].rmz;                        /* 恢复解的顺序*/
            x[k].rmz = x[exjs[k]].rmz;
            x[exjs[k]].rmz = tmp;
            tmp = x[k].imz;
            x[k].imz = x[exjs[k]].imz;
            x[exjs[k]].imz = tmp;
        }
    }

    free(exjs);                                  /* 释放分配的空间*/
    return (1);                                /* 求解成功，返回1*/
}
