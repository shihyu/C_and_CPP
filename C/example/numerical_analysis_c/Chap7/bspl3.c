#include "stdio.h"
#include "math.h"
/*======================================================
// 函数名：bspl3
// 功能描述：第三类边界条件的三次样条函数插值
// 输入参数：x 指向存放n个结点的数据的数组的指针
//           y 指向存放n个结点的函数值的数组的指针
//           n 结点个数，本函数要求n至少为3
//           t 指向存放m个插值点的数据的数组的指针
//           m 插值点个数
//           z 指向存放返回的m个插值点处的函数近似值的数组的指针
//           z1 指向存放返回的m个插值点处的函数一阶导数的数组的指针
//           z2 指向存放返回的m个插值点处的函数二阶导数的数组的指针
// 返回值：  成功则返回整型 1，失败则返回 0
=========================================================*/
int bspl3(x, y, n, t, m, z, z1, z2)
double* x, *y;
double* t, *z, *z1, *z2;
int m, n;
{
    int i, j, k;
    double y0, y1, *a, *b, *c, *p, *q, alpha, beta, *dy; /* 计算dy所用变量*/
    double h1, h2, h3;                       /* 计算z z1 z2时所用的变量*/
    double t1, t2, t3, t4;                      /* 计算z z1 z2时所用的四个系数*/
    double tmp;

    if (!(x && y && t && z && z1 && z2)) {      /* 检测输入指针是否为空*/
        printf("Pointer is Null\n");
        return (0);
    }

    if (n < 3) {                                /* 提供结点少于3就不进行插值了*/
        printf("nodes less than 3");
        return (0);
    }

    dy = (double*)malloc(n * sizeof(double));    /* 分配空间并检测是否成功*/
    a = (double*)malloc(n * sizeof(double));
    b = (double*)malloc(n * sizeof(double));
    c = (double*)malloc(n * sizeof(double));
    p = (double*)malloc(n * sizeof(double));
    q = (double*)malloc(n * sizeof(double));

    if (!(dy && a && b && c && p && q)) {
        free(dy);
        free(a);
        free(b);
        free(c);
        free(p);
        free(q);
        printf("Memory alloc failed\n");
        return (0);
    }

    a[0] = 0.0;                                         /* a数组赋初值*/
    b[0] = 1.0;                                         /* b数组赋初值*/
    c[0] = 0.0;                                         /* c数组赋初值*/
    h1 = x[n - 1] - x[n - 2];
    y0 = y[n - 1] - y[n - 2];

    for (i = 1; i < n - 1; i++) {                        /* 递推计算a,b,c*/
        h2 = h1;
        y1 = y0;
        h1 = x[i] - x[i - 1];
        y0 = y[i] - y[i - 1];
        alpha = h2 / (h2 + h1);
        beta = (1.0 - alpha) * y1 / h2;
        beta = 3.0 * (beta + alpha * y0 / h1);
        tmp = 1.0 / (2.0 + (1.0 - alpha) * a[i - 1]);
        a[i] = -alpha * tmp;
        b[i] = (alpha - 1.0) * b[i - 1] * tmp;
        c[i] = (beta + (alpha - 1.0) * c[i - 1]) * tmp;
    }

    h2 = x[n - 1] - x[n - 2];                       /* 计算最后一个alpha和beta*/
    y1 = y[n - 1] - y[n - 2];
    alpha = h1 / (h1 + h2);
    beta = (1.0 - alpha) * y0 / h1;
    beta = 3.0 * (beta + alpha * y1 / h2);
    p[n - 2] = 1.0;                                 /* 计算p,q值*/
    q[n - 2] = 0.0;

    for (i = n - 2; i > 0; i--) {
        p[i - 1] = a[i] * p[i] + b[i];
        q[i - 1] = a[i] * q[i] + c[i];
    }

    dy[n - 2] = (beta - alpha * q[0] + (alpha - 1.0) * q[n - 3]); /* dy赋初值*/
    dy[n - 2] = dy[n - 2] / (2.0 + alpha * p[0] + (1.0 - alpha) * p[n - 3]);

    for (i = 0; i < n - 2; i++) {                 /* 递推计算结点处的一阶导数dy*/
        dy[i] = p[i] * dy[n - 2] + q[i];
    }

    dy[n - 1] = dy[0];

    for (k = 0; k < m; k++) {
        tmp = t[k];
        j = 0;

        while ((x[j] < tmp) && (j < n)) {             /* 寻找合适的区间*/
            j++;
        }

        j = j - 1;

        if (j < 1) {
            j = 0;
        }

        if (j > (n - 1)) {
            j = n - 2;
        }

        h1 = x[j + 1] - x[j];                         /* h*/
        h2 = h1 * h1;                                /* h^2*/
        h3 = h2 * h1;                                /* h^3*/
        t1 = 3.0 * y[j + 1] / h2 - 1.0 * dy[j + 1] / h1; /* 计算4个系数*/
        t2 = 2.0 * y[j + 1] / h3 - 1.0 * dy[j + 1] / h2;
        t3 = 3.0 * y[j] / h2 + 1.0 * dy[j] / h1;
        t4 = 2.0 * y[j] / h3 + 1.0 * dy[j] / h2;
        z[k] = (t1 - t2 * (tmp - x[j])) * (tmp - x[j]) * (tmp -
                x[j]); /* 计算函数近似值*/
        z[k] = z[k] + (t3 - t4 * (x[j + 1] - tmp)) * (x[j + 1] - tmp) *
               (x[j + 1] - tmp);
        z1[k] = (2.0 * t1 - 3.0 * t2 * (tmp - x[j])) * (tmp - x[j]); /* 计算一阶导数*/
        z1[k] = z1[k] + (-2.0 * t3 + 3.0 * t4 * (x[j + 1] - tmp)) * (x[j + 1] - tmp);
        z2[k] = 2.0 * t1 - 6.0 * t2 * (tmp - x[j]);         /* 计算二阶导数*/
        z2[k] = z2[k] + 2.0 * t3 - 6.0 * t4 * (x[j + 1] - tmp);
    }

    free(dy);
    free(a);
    free(b);
    free(c);
    free(p);
    free(q);
    return (1);
}
