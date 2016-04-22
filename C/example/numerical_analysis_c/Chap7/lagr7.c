#include "stdio.h"
#include "math.h"
/*======================================================
// 函数名：lagr7
// 功能描述：拉格朗日全区间插值
// 输入参数：x 指向存放n个结点的数据的数组的指针
//           y 指向存放n个结点的函数值的数组的指针
//           n 结点个数
//           t 指定的插值点
// 返回值：  在指定插值点的函数近似值
=========================================================*/
double lagr7(x, y, n, t)
double* x, *y, t;
int n;
{
    int i, j, k, p;
    double z, tmp;

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

    if (n == 2) {
        z = (y[0] * (t - x[1]) - y[1] * (t - x[0])) / (x[0] - x[1]);
        return (z);
    }

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

    z = 0.0;
    printf("lagr7: %d,%d\n", k, k + p - 1); /* 打印使用的区间*/

    for (i = k; i < k + p; i++) {        /* 求出插值的结果*/
        tmp = 1.0;

        for (j = k; j < k + p; j++)
            if (j != i) {
                tmp = tmp * (t - x[j]) / (x[i] - x[j]);
            }

        z = z + tmp * y[i];
    }

    return (z);
}
