/*=============================================================
// 函 数 名：rads
// 功能描述：基数排序
// 输入参数： x 存放待排序数据的数组
//            n 数组长度
//            d 数据的位数
//            k 每位数字最多在[0,k)之间，也就是说是k进制的。
// 返 回 值：无
//==============================================================*/
#include "stdlib.h"
void rads(x, n, d, k)
int* x;
int n, d, k;
{
    int i, j, m, k1, *a, *y, flag;
    void rads_cout();
    a = (int*)malloc(n * sizeof(int));      /* a是存放一位数字的数组*/
    y = (int*)malloc(n * sizeof(int));      /* y是用于存放中间变量的空间*/
    flag = 0;
    k1 = 1;

    for (m = 0; m < d; m++) {               /* 分别按d位进行排序*/
        if (flag == 0) {
            for (j = 0; j < n; j++) {
                a[j] = x[j] / k1;           /* 得到了第m位*/
                a[j] = a[j] % k;
            }

            rads_cout(a, x, y, n, k);
        } else {
            for (j = 0; j < n; j++) {
                a[j] = y[j] / k1;           /* 得到了第m位*/
                a[j] = a[j] % k;
            }

            rads_cout(a, y, x, n, k);
        }

        flag = 1 - flag;
        k1 = k1 * k;
    }

    if (flag == 1)                          /* 此时排序后数据存放在y中*/
        for (j = 0; j < n; j++) {
            x[j] = y[j];
        }

    free(a);
    free(y);
    return;
}

void rads_cout(a, x, y, n, k)               /* 将x按a排序，结果放在y中*/
int* a, *x, *y;
int n, k;
{
    int i, j, *c;
    c = (int*)malloc((k + 1) * sizeof(int));

    for (i = 0; i <= k; i++) {              /* 设置初值*/
        c[i] = 0;
    }

    for (i = 0; i < n; i++) {               /* 统计个数*/
        j = a[i];
        c[j] = c[j] + 1;
    }

    for (i = 1; i <= k; i++) {              /* 计数，用于计算位置*/
        c[i] = c[i] + c[i - 1];
    }

    for (i = n - 1; i >= 0; i--) {          /* 直接各归其位*/
        j = a[i];
        y[c[j] - 1] = x[i];
        c[j] = c[j] - 1;
    }

    free(c);
    return;
}
