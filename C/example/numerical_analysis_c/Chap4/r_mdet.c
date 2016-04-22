/*======================================================
//函数名：r_mdet
//功能描述：求实矩阵的行列式值
//输入参数：mat(输入的矩阵) n(矩阵阶数) eps(精度)
//返回值：矩阵的行列式值
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

double r_mdet(mat, n, eps)
double* mat, eps;
int n;
{
    int i, j, k, is, js, l, v;
    double det, flag, tmp, pivot;
    double* cpmat;

    if (mat == NULL) {                         /* 检查输入的指针是否为空*/
        printf("matrix pointer is NULL.\n");
        return (0.0);
    }

    cpmat = (double*)malloc(n * n * sizeof(
                                double)); /* 将输入矩阵的内容拷贝一份，以免破坏*/

    for (i = 0; i < n * n; i++) {
        cpmat[i] = mat[i];
    }

    det = 1.0;                                 /* 设置行列式值初置*/
    flag = 1.0;                                /* 这个变量原来记录行列式值的符号*/

    for (k = 0; k < n - 1; k++) {  /* 最多进行n-1次消去*/
        pivot = 0.0;                             /* 选择主元*/

        for (i = k; i < n; i++)
            for (j = k; j < n; j++) {
                tmp = fabs(cpmat[i * n + j]);

                if (tmp > pivot) {
                    pivot = tmp;
                    is = i;
                    js = j;
                }
            }

        if (pivot < eps) {                       /* 如果找到的主元小于eps，则认为是0。*/
            det = 0.0;                             /*此时行列式值也是0。*/
            return (det);
        }

        if (is != k) {                           /* 判断是否需要行交换*/
            flag = -flag;                          /* 行交换一次，行列式值变号*/

            for (j = k; j < n; j++) {              /* 进行行交换*/
                l = k * n + j;
                v = is * n + j;
                tmp = cpmat[l];
                cpmat[l] = cpmat[v];
                cpmat[v] = tmp;
            }
        }

        if (js != k) {                           /* 判断是否需要列交换*/
            flag = -flag;                          /* 列交换一次，行列式值变号*/

            for (i = k; i < n; i++) {              /* 进行列交换*/
                l = i * n + k;
                v = i * n + js;
                tmp = cpmat[l];
                cpmat[l] = cpmat[v];
                cpmat[v] = tmp;
            }
        }

        for (i = k + 1; i < n; i++) {           /* 进行消去*/
            tmp = cpmat[i * n + k] / cpmat[k * n + k]; /* 记录下此值，减少除法的次数*/

            for (j = k + 1; j < n; j++) {         /* 消去*/
                cpmat[i * n + j] -= tmp * cpmat[k * n + j];
            }
        }

        det = det * cpmat[k * n + k];     /*更新det的值*/
    }

    det = flag * det * cpmat[k * n + k]; /* 最终更新det的值*/
    free(cpmat);
    return (det);
}
