#include "stdio.h"
#include "math.h"
/*======================================================
// 函数名：hmte
// 功能描述：埃尔米特等距插值
// 输入参数：x 第一个结点，h 结点的距离
//           y 指向存放n个结点的函数值的数组的指针
//           dy 指向存放n个结点的一阶导数的数组的指针
//           n 结点个数
//           t 指定的插值点
// 返回值：  在指定插值点的函数近似值
=========================================================*/
double hmte(x, h, y, dy, n, t)
double x, h, *y, *dy, t;
int n;
{
    int i, j, k, p;
    double z, tmp, l, ll;

    if ((y == NULL) || (dy == NULL)) { /* 检测输入指针是否为空*/
        printf("Pointer is Null\n");
        return (0.0);
    }

    if (n < 1) {                         /* 没有提供结点，返回0.0*/
        return (0.0);
    }

    if (n == 1) {
        /* 只有一个结点时*/
        z = y[0] + dy[0] * (t - x);
        return (z);
    }

    if (t < (x + 2 * h)) {
        k = 0;
        p = 3;
    } else if (t > (x + (n - 3)*h)) {
        k = n - 3;
        p = 3;
    } else {
        k = (int)((t - x) / h);             /* 等距时，可以直接计算出所用区间*/

        if (n > 7) {
            if (k < 4) {
                k = 0;
                p = 2;
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
    printf("hmte: %d,%d\n", k, k + p - 1); /* 打印使用的区间*/

    for (i = k; i < k + p; i++) {        /* 求出插值的结果*/
        l = 1.0;                           /* 计算H(x)*/

        for (j = k; j < k + p; j++)
            if (j != i) {
                l = l * (t - x - j * h) / (i - j);
            }

        l = l / pow(h, p - 1);
        ll = 0.0;                          /* 计算H'(x)*/

        for (j = k; j < k + p; j++)
            if (j != i) {
                ll = ll + 1.0 / (i - j);
            }

        ll = ll / h;
        tmp = y[i] + (t - x - i * h) * (dy[i] - 2.0 * y[i] * ll);
        z = z + tmp * l * l;;
    }

    return (z);
}
