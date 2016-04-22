#include "stdio.h"
#include "stdlib.h"
#include "c_comp.c"

/*======================================================
// 函数名：c_minv
// 功能描述：用高斯－约当消去法进行复矩阵原地求逆
// 输入参数：mat 待求逆的矩阵，求解成功后存放逆矩阵
//           n 矩阵阶数
//           eps 精度要求，小于eps的值，认为是0。
// 返回值：整型。运行成功则返回1,失败则返回0
=========================================================*/
int c_minv(mat, n, eps)
struct c_comp* mat;
int n;
double eps;
{
    int* is, *js, i, j, k, l, v;
    struct c_comp c_tmp;
    double tmp, d;

    if (mat == NULL) {                  /* 检测输入的指针是否为空*/
        printf("The matrix pointer is NULL\n");
        return (0);
    }

    is = malloc(n * sizeof(int));       /* 为行交换记录分配空间并检测是否成功*/

    if (is == NULL) {
        printf("Memory alloc failed\n");
        return (0);
    }

    js = malloc(n * sizeof(int));       /* 为列交换记录分配空间并检测是否成功*/

    if (js == NULL) {
        free(is);
        printf("Memory alloc failed\n");
        return (0);
    }

    for (k = 0; k < n; k++) {
        d = 0.0;

        for (i = k; i < n; i++)        /* 此循环用于选取主元*/
            for (j = k; j < n; j++) {
                l = i * n + j;
                tmp = mat[l].rmz * mat[l].rmz + mat[l].imz * mat[l].imz; /* 求元素的模*/

                if (tmp > d) {
                    d = tmp;
                    is[k] = i;
                    js[k] = j;
                }
            }

        if (d < eps) {                 /* 判断主元是否过小*/
            free(is);                  /* 若主元过小则退出程序*/
            free(js);
            printf("Matrix inverse failed.\n");
            return (0);
        }

        if (is[k] != k)                /* 判断是否需要行交换*/
            for (j = 0; j <= n - 1; j++) { /* 进行行交换*/
                l = k * n + j;
                v = is[k] * n + j;
                tmp = mat[l].rmz;
                mat[l].rmz = mat[v].rmz;
                mat[v].rmz = tmp;
                tmp = mat[l].imz;
                mat[l].imz = mat[v].imz;
                mat[v].imz = tmp;
            }

        if (js[k] != k)                /* 判断是否需要列交换*/
            for (i = 0; i <= n - 1; i++) { /* 进行列交换*/
                l = i * n + k;
                v = i * n + js[k];
                tmp = mat[l].rmz;
                mat[l].rmz = mat[v].rmz;
                mat[v].rmz = tmp;
                tmp = mat[l].imz;
                mat[l].imz = mat[v].imz;
                mat[v].imz = tmp;
            }

        l = k * n + k;                 /* 归一化计算的第一步*/
        mat[l].rmz = mat[l].rmz / d;
        mat[l].imz = -mat[l].imz / d;

        for (j = 0; j <= n - 1; j++)   /* 归一化计算的第二步，需要使用复数的乘法*/
            if (j != k) {
                v = k * n + j;
                c_comp_product(&mat[v], &mat[l], &mat[v]);
            }

        for (i = 0; i <= n - 1; i++)   /* 消元计算的第一步*/
            if (i != k) {
                for (j = 0; j <= n - 1; j++)
                    if (j != k) {
                        c_comp_product(&mat[k * n + j], &mat[i * n + k], &c_tmp);
                        mat[i * n + j].rmz = mat[i * n + j].rmz - c_tmp.rmz;
                        mat[i * n + j].imz = mat[i * n + j].imz - c_tmp.imz;
                    }
            }

        for (i = 0; i <= n - 1; i++)   /* 消元计算的第二步*/
            if (i != k) {
                v = i * n + k;
                c_comp_product(&mat[l], &mat[v], &mat[v]);
                mat[v].rmz = -mat[v].rmz;
                mat[v].imz = -mat[v].imz;
            }
    }

    for (k = n - 1; k >= 0; k--) {    /* 依照行交换和列交换的历史进行结果恢复*/
        if (js[k] != k)               /* 判断是否需要恢复*/
            for (j = 0; j <= n - 1; j++) { /* 按列交换的历史进行行交换*/
                l = k * n + j;
                v = js[k] * n + j;
                tmp = mat[l].rmz;
                mat[l].rmz = mat[v].rmz;
                mat[v].rmz = tmp;
                tmp = mat[l].imz;
                mat[l].imz = mat[v].imz;
                mat[v].imz = tmp;
            }

        if (is[k] != k)
            for (i = 0; i <= n - 1; i++) { /* 按行交换的历史进行列交换*/
                l = i * n + k;
                v = i * n + is[k];
                tmp = mat[l].rmz;
                mat[l].rmz = mat[v].rmz;
                mat[v].rmz = tmp;
                tmp = mat[l].imz;
                mat[l].imz = mat[v].imz;
                mat[v].imz = tmp;
            }
    }

    free(is);                          /* 释放分配的空间*/
    free(js);
    return (1);                        /* 求解成功，返回1*/
}
