#include "stdio.h"
#include "math.h"
/*======================================================
// 函数名：atken
// 功能描述：埃特金插值
// 输入参数：x 指向存放n个结点的数据的数组的指针
//           y 指向存放n个结点的函数值的数组的指针
//           n 结点个数
//           t 指定的插值点, eps 小于此数的值认为是0
// 返回值：  在指定插值点的函数近似值
=========================================================*/
double atken(x, y, n, t, eps)
double* x, *y, t, eps;
int n;
{
    int i, j, k, m;
    double z, d, xx[8], yy[8];

    if ((x == NULL) || (y == NULL)) {          /* 检测输入指针是否为空*/
        printf("Pointer is Null\n");
        return (0.0);
    }

    if (n < 1) {                               /* 没有提供数据点时，返回0*/
        return (0.0);
    }

    if (n == 1) {                              /* 只有一个数据点时，就返回这个点*/
        return (y[0]);
    }

    if (n == 2) {                              /* 只有两个数据点时，都要用*/
        k = 0;
        m = 2;
    } else if (t < x[2]) {                    /* 有大于等于3个数据点时，边缘的情况*/
        k = 0;
        m = 3;
    } else if (t > x[n - 3]) {                /* 数据处在较大的边缘的情况*/
        k = n - 3;
        m = 3;
    } else {
        k = 0;
        m = n - 1;                        /* 二分法寻找合适的区间*/

        while ((m - k) > 1) {
            j = (k + m) / 2;

            if (x[j] < t) {
                k = j;
            } else {
                m = j;
            }
        }

        if (n > 7) {
            if (k < 4) {                           /* 插值点在中间*/
                k = 0;
                m = 2 * m;
            } else if (k > (n - 5)) {              /* 插值点在中间*/
                m = 2 * (n - 1 - k);
                k = n - m;
            } else {
                k = k - 3;    /* 插值点在中间,此时n>=k+5*/
                m = 8;
            }
        } else {
            k = 0;
            m = n;
        }
    }

    printf("atken: %d,%d\n", k, k + m - 1);

    for (i = 0; i < m; i++) {                   /* 将使用的m个数据转存在xx,yy中*/
        xx[i] = x[k + i];
        yy[i] = y[k + i];
    }

    i = 1;

    do {                                        /* 埃特金逐步插值*/
        z = yy[i];

        for (j = 0; j < i; j++) {
            z = yy[j] + (t - xx[j]) * (yy[j] - z) / (xx[j] - xx[i]);
        }

        yy[i] = z;
        d = fabs(yy[i] - yy[i - 1]);              /* 比较两次插值的结果*/
        i++;
    } while ((i < m) && (d > eps));             /* 检查是否满足精度要求*/

    return (z);
}
