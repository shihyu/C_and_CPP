/*======================================================
//函数名：rungekuttavh
//功能描述：变步长龙格-库塔算法求常微分方程组的初值问题
//输入参数：*y（ 指向函数初值以及函数返回值的指针n*(m+1)）
//          n（方程组个数），f（目标函数的计算）
//          h（步长），m（步数），a（区间起点），eps（精度）
//返回值：0（失败），1（成功）
=========================================================*/
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
//#include"rungekuttainvh.c"

int rungekuttavh(y, n, f, h, m, a, eps)
double* y, (*f)(), h, a, eps;
int n, m;
{
    double x, *y1, *y2, *ytemp1, *ytemp2, dis, ht = h;
    int k = 0, i, m1, m2;

    y1 = (double*)malloc(sizeof(double) * n);  /* 动态分配*/
    y2 = (double*)malloc(sizeof(double) * n);

    if (y1 == NULL || y2 == NULL) {
        printf("memory alloc failed.\n");
        return (0);
    }

    do {                                       /* 对k进行循环，分别计算xk处的函数值*/
        x = a + k * h;

        do {                                   /* 在每个xk处，进行步长的动态选择*/
            m1 = (int)(h / ht);                /* ht为步长*/
            ytemp1 = (double*)malloc(sizeof(double) * n * (m1 + 1));

            if (ytemp1 == NULL) {
                printf("memory alloc failed.\n");
                return (0);
            }

            for (i = n; i < n * (m1 + 1); i++) {
                ytemp1[i] = 0.0;    /* 初始化*/
            }

            for (i = 0; i < n; i++) {
                ytemp1[i] = y[k * n + i];
            }

            rungekuttainvh(ytemp1, n, f, ht, m1, x); /* 调用定步长公式*/

            for (i = 0; i < n; i++) {
                y1[i] = ytemp1[m1 * n + i];
            }

            free(ytemp1);

            m2 = 2 * m1;                             /* ht/2为步长*/
            ytemp2 = (double*)malloc(sizeof(double) * n * (m2 + 1));

            if (ytemp2 == NULL) {
                printf("memory alloc failed.\n");
                return (0);
            }

            for (i = n; i < n * (m2 + 1); i++) {
                ytemp2[i] = 0.0;
            }

            for (i = 0; i < n; i++) {
                ytemp2[i] = y[k * n + i];
            }

            rungekuttainvh(ytemp2, n, f, ht / 2, m2, x);

            for (i = 0; i < n; i++) {
                y2[i] = ytemp2[m2 * n + i];
            }

            free(ytemp2);

            ht = ht / 2;                             /* 下一次循环的步长*/

            dis = 0.0;                               /* max距离*/

            for (i = 0; i < n; i++)
                if (dis < fabs(y1[i] - y2[i])) {     /* 计算此处的函数值*/
                    dis = fabs(y1[i] - y2[i]);
                }
        } while (dis >= eps);                        /* 看距离是否满足精度*/

        for (i = 0; i < n; i++) {
            y[(k + 1)*n + i] = y2[i];    /* 结果记录*/
        }

        k++;                                         /* 下一个xk*/
    } while (k < m);                                 /* m个xk的循环*/

    free(y1);
    free(y2);
    return (1);
}


