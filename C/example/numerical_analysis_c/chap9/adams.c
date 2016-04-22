/*======================================================
//函数名：adams
//功能描述：阿当姆斯预报校正法求常微分方程组的初值问题
//输入参数：*y（ 指向函数初值以及函数返回值的指针n*(m+1)
//          n（方程组个数），f（斜率的计算）
//          h（步长），m（步数），a（区间起点）
//返回值：0（失败），1（成功）
=========================================================*/
#include "rungekuttainvh.c"

int adams(y, n, f, h, m, a)
double* y, (*f)(), h, a;
int n, m;
{
    double* f1, *f2, *f3, *f4, *f5, *temp, *ytemp, x;
    int k = 3, i;
    f1 = (double*)malloc(sizeof(double) * n);           /* 微分方程斜率*/
    f2 = (double*)malloc(sizeof(double) * n);
    f3 = (double*)malloc(sizeof(double) * n);
    f4 = (double*)malloc(sizeof(double) * n);
    f5 = (double*)malloc(sizeof(double) * n);
    ytemp = (double*)malloc(sizeof(double) * n);

    if (f1 == NULL || f2 == NULL || f3 == NULL || f4 == NULL || f5 == NULL ||
        ytemp == NULL) {
        printf("memory alloc failed.\n");
        return (0);
    }

    rungekuttainvh(y, n, f, h, 3,
                   a);                   /* 用龙格-库塔法计算前4个初值*/
    {
        x = a + k * h;
        f(&y[(k - 3)*n], f1, x - 3 * h);                /* x(k-3)处的f*/
        f(&y[(k - 2)*n], f2, x - 2 * h);                /* x(k-2)处的f*/
        f(&y[(k - 1)*n], f3, x - h);                    /* x(k-1)处的f*/
        f(&y[k * n], f4, x);                            /* xk处的f*/

        for (i = 0; i < n; i++) {                       /* 预报*/
            ytemp[i] = y[k * n + i] + h / 24.0 * (55.0 * f4[i] - 59.0 * f3[i] + 37.0 * f2[i]
                                                  - 9.0 * f1[i]);
        }

        f(ytemp, f5, x + h);                            /* x(k+1)处的f*/

        for (i = 0; i < n; i++) {                       /* 校正*/
            y[(k + 1)*n + i] = y[k * n + i] + h / 24.0 * (9.0 * f5[i] + 19.0 * f4[i] - 5.0 *
                               f3[i] + f2[i]);
        }

        k++;
    }

    while (k < m) {                                     /* 循环*/
        x = a + k * h;
        temp = f1;
        f1 = f2;
        f2 = f3;
        f3 = f4;
        f4 = temp;
        f(&y[k * n], f4, x);                            /* f4*/

        for (i = 0; i < n; i++) {
            ytemp[i] = y[k * n + i] + h / 24.0 * (55.0 * f4[i] - 59.0 * f3[i] + 37.0 * f2[i]
                                                  - 9.0 * f1[i]);
        }

        f(ytemp, f5, x + h);                            /* k3*/

        for (i = 0; i < n; i++) {
            y[(k + 1)*n + i] = y[k * n + i] + h / 24.0 * (9.0 * f5[i] + 19.0 * f4[i] - 5.0 *
                               f3[i] + f2[i]);
        }

        k++;
    }

    free(f1);
    free(f2);
    free(f3);
    free(f4);
    free(f5);
    free(ytemp);
    return (1);
}

