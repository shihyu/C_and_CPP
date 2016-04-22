#include "stdio.h"
#include "math.h"
/*======================================================
// 函数名：lagr2
// 功能描述：拉格朗日抛物线插值
// 输入参数：x 指向存放n个结点的数据的数组的指针
//           y 指向存放n个结点的函数值的数组的指针
//           n 结点个数
//           t 指定的插值点
// 返回值：  在指定插值点的函数近似值
=========================================================*/
double lagr2(x, y, n, t)
double* x, *y, t;
int n;
{
    int i, j, k;
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

    k = 0;

    while ((x[k] < t) && (k < n)) {      /* 寻找合适的区间*/
        k++;
    }

    k = k - 1;

    if (k < 1) {
        k = 0;
    }

    if (k > (n - 3)) {
        k = n - 3;
    }

    z = 0.0;
    printf("lagr2: %d,%d\n", k, k + 2);  /* 打印使用的区间*/

    for (i = k; i < k + 3; i++) {        /* 求出插值的结果*/
        tmp = 1.0;

        for (j = k; j < k + 3; j++)
            if (j != i) {
                tmp = tmp * (t - x[j]) / (x[i] - x[j]);
            }

        z = z + tmp * y[i];
    }

    return (z);
}
