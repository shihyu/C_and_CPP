/*======================================================
// 函数名：lfs
// 功能描述：连分式插值
// 输入参数：x 指向存放n个结点的数据的数组的指针
//           y 指向存放n个结点的函数值的数组的指针
//           n 结点个数
//           t 指定的插值点, eps 小于此数的值认为是0
// 返回值：  在指定插值点的函数近似值
=========================================================*/
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

double lfs(x, y, n, t, eps)
double* x, *y, t, eps;
int n;
{
    int i, j, k, p, flag;
    double z, u, *b;

    if ((x == NULL) || (y == NULL)) {    /* 检测输入指针是否为空*/
        printf("Pointer is Null\n");
        return (0.0);
    }

    if (n < 1) {                         /* 没有提供结点，返回0.0*/
        return (0.0);
    }

    if (n == 1) {                        /* 只有一个结点，返回此函数值*/
        return (y[0]);
    }

    k = 0;

    if (t < x[2]) {
        k = 0;
        p = 3;
    } else if (t > x[n - 3]) {
        k = n - 3;
        p = 3;
    } else {
        k = 0;
        p = n - 1;                  /* 二分法寻找合适的区间*/

        while ((p - k) > 1) {
            j = (k + p) / 2;

            if (x[j] < t) {
                k = j;
            } else {
                p = j;
            }
        }

        if (n > 7) {
            if (k < 4) {
                k = 0;
                p = 2 * p;
            } else if (k > (n - 5)) {
                p = 2 * (n - 1 - k);
                k = n - p;
            } else {
                k = k - 3;
                p = 8;
            }
        } else {
            k = 0;
            p = n;
        }
    }

    b = (double*)malloc((p) * sizeof(double)); /* 分配空间，存放连分式*/
    b[0] = y[k];

    for (i = 1; i < p; i++) {                 /* 构造连分式*/
        flag = 0;
        u = y[i + k];

        for (j = 0; j < i; j++) {
            if (fabs(u - b[j]) < eps) {             /* 要做除数，因此需要检查范围*/
                flag = 1;
                j = i;                                /* 若除数为0,则连分式到此为止*/
            } else {
                u = (x[i + k] - x[j + k]) / (u - b[j]);
            }
        }

        if (flag == 1) {
            /* 这个数据用来终止连分式*/
            b[i] = 1.0e35;                          /* 连分式的节数*/
            p = i;
        } else {
            b[i] = u;
        }
    }

    printf("lfs: %d,%d\n", k, k + p - 1);        /* 打印构造连分式所使用的区间*/
    z = b[p - 1];                                /* 计算近似值*/

    for (i = p - 2; i >= 0; i--) {
        z = b[i] + (t - x[i + k]) / z;
    }

    free(b);
    return (z);
}
