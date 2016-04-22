/*======================================================
// 函数名：lsq2
// 功能描述：矩形区域最小二乘拟合
// 输入参数：x 指向存放n个X坐标的数组的指针
//           y 指向存放m个Y坐标的数组的指针
//           z 指向存放n*m个结点的函数值的数组的指针
//           n X坐标的个数
//           m Y坐标的个数
//           p 指向存放pp*qq个拟合多项式系数的数组的指针
//           pp 拟合多项式中x的最高次数+1
//           qq 拟合多项式中y的最高次数+1
//           s 指向数组的指针，存放5个数据，依次返回的是：各点误差的平方和
//            误差的绝对值的最大值、误差的绝对值之和,x的平均值, y的平均值
// 返回值：  整型。若拟合成功则返回1,否则返回0
=========================================================*/
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
int lsq2(x, y, z, n, m, p, pp, qq, s)
double* x, *y, *z, *p, *s;
int n, m, qq, pp;
{
    int i, j, k, l, k0, k1, k2, l0, l1, l2;
    double a, b, d0, d1, d2, t, t2, x1, y1;
    double* x0, *y0;                             /* 存放预处理后的X坐标和Y坐标*/
    double* qx, *qy;                             /* 存放X和Y上各个正交多项式的系数*/
    double* q0x, *q1x, *q2x;                     /* 存放X上正交多项式在n点上的值*/
    double* q0y, *q1y, *q2y;                     /* 存放Y上正交多项式在m点上的值*/
    double* c, *u;                               /* 存放系数c(pp*m) 和 u(pp*qq)*/

    if (!(x && y && z && p && s)) {                       /* 检测输入指针是否为空*/
        printf("Pointer is Null\n");
        return (0);
    }

    x0 = (double*)malloc(n * sizeof(double));
    y0 = (double*)malloc(m * sizeof(double));
    qx = (double*)malloc(pp * pp * sizeof(double));   /* 分配空间并检测是否成功*/
    qy = (double*)malloc(qq * qq * sizeof(double));
    q0x = (double*)malloc(n * sizeof(double));
    q1x = (double*)malloc(n * sizeof(double));
    q2x = (double*)malloc(n * sizeof(double));
    q0y = (double*)malloc(m * sizeof(double));
    q1y = (double*)malloc(m * sizeof(double));
    q2y = (double*)malloc(m * sizeof(double));
    c = (double*)malloc(pp * m * sizeof(double));
    u = (double*)malloc(pp * qq * sizeof(double));

    if (!(x0 && y0 && qx && qy && q0x && q1x && q2x && q0y && q1y && q2y && c &&
          u)) {
        free(x0);
        free(y0);
        free(qx);
        free(qy);
        free(q0x);
        free(q1x);
        free(q2x);
        free(q0y);
        free(q1y);
        free(q2y);
        free(c);
        free(u);
        printf("Memory alloc Failed\n");
        return (0);
    }

    t = 0.0;                                          /* 预处理X坐标*/

    for (i = 0; i < n; i++) {
        t = t + x[i] / n;
    }

    for (i = 0; i < n; i++) {
        x0[i] = x[i] - t;
    }

    s[3] = t;
    t = 0.0;                                          /* 预处理Y坐标*/

    for (j = 0; j < m; j++) {
        t = t + y[j] / m;
    }

    for (j = 0; j < n; j++) {
        y0[j] = y[j] - t;
    }

    s[4] = t;

    for (i = 0; i < pp; i++)                          /* 设初值*/
        for (j = 0; j < pp; j++) {
            qx[i * pp + j] = 0.0;
        }

    for (i = 0; i < qq; i++)                          /* 设初值*/
        for (j = 0; j < qq; j++) {
            qy[i * qq + j] = 0.0;
        }

    for (i = 0; i < n; i++) {                         /* Q0的函数值*/
        q0x[i] = 1.0;
    }

    qx[0] = 1;                                        /* Q0的系数*/
    d0 = n;

    for (j = 0; j < m; j++) {                         /* 计算系数c0j*/
        t = 0.0;

        for (i = 0; i < n; i++) {
            t = t + z[i * m + j] / d0;
        }

        c[j] = t;
    }

    /* X方向的计算*/
    for (i = 0; i < n; i++) {                         /* Q1的函数值*/
        q1x[i] = x0[i];
    }

    qx[pp + 1] = 1.0;                                   /* Q1的系数*/
    d1 = 0.0;

    for (i = 0; i < n; i++) {
        d1 = d1 + q1x[i] * q1x[i];
    }

    for (j = 0; j < m; j++) {                         /* 计算系数c1j*/
        t = 0.0;

        for (i = 0; i < n; i++) {
            t = t + q1x[i] * z[i * m + j] / d1;
        }

        c[m + j] = t;
    }

    k0 = 0;
    k1 = pp;

    for (k = 2; k < pp; k++) {                      /* 依次构造第k个X上正交多项式*/
        a = 0.0;                                       /* 计算a*/

        for (i = 0; i < n; i++) {
            a = a + x0[i] * q1x[i] * q1x[i];
        }

        a = a / d1;
        b = d1 / d0;                                   /* 计算b*/
        d2 = 0;

        for (i = 0; i < n; i++) {                      /* 计算Qi的函数值和d*/
            t = (x0[i] - a) * q1x[i] - b * q0x[i];
            q2x[i] = t;
            d2 = d2 + t * t;
        }

        for (j = 0; j < m; j++) {                      /* 计算系数ckj*/
            t = 0.0;

            for (i = 0; i < n; i++) {
                t = t + q2x[i] * z[i * m + j];
            }

            c[k * m + j] = t / d2;
        }

        k2 = k1 + pp;
        qx[k2] = -a * qx[k1] - b * qx[k0];             /* 计算Qi的系数*/
        qx[k2 + k] = 1.0;

        for (j = 1; j < k; j++) {
            qx[k2 + j] = qx[k1 + j - 1] - a * qx[k1 + j] - b * qx[k0 + j];
        }

        d0 = d1;
        d1 = d2;                              /* 循环使用变量*/
        k0 = k1;
        k1 = k2;

        for (i = 0; i < n; i++) {                      /* 循环使用数组*/
            q0x[i] = q1x[i];
            q1x[i] = q2x[i];
        }
    }

    /* Y方向的计算*/
    for (j = 0; j < m; j++) {                         /* Q0的函数值*/
        q0y[j] = 1.0;
    }

    qy[0] = 1;                                        /* Q0的系数*/
    d0 = m;

    for (k = 0; k < pp; k++) {                        /* 计算系数uk0*/
        t = 0.0;

        for (j = 0; j < m; j++) {
            t = t + c[k * m + j] / d0;
        }

        u[k * qq] = t;
    }

    for (j = 0; j < m; j++) {                         /* Q1的函数值*/
        q1y[j] = y0[j];
    }

    qy[qq + 1] = 1.0;                                 /* Q1的系数*/
    d1 = 0.0;

    for (j = 0; j < m; j++) {
        d1 = d1 + q1y[j] * q1y[j];
    }

    for (k = 0; k < pp; k++) {                         /* 计算系数uk1*/
        t = 0.0;

        for (j = 0; j < m; j++) {
            t = t + c[k * m + j] * q1y[j] / d1;
        }

        u[k * qq + 1] = t;
    }

    l0 = 0;
    l1 = qq;

    for (l = 2; l < qq; l++) {                      /* 依次构造第l个Y上正交多项式*/
        a = 0.0;                                       /* 计算a*/

        for (j = 0; j < m; j++) {
            a = a + y0[j] * q1y[j] * q1y[j];
        }

        a = a / d1;
        b = d1 / d0;                                   /* 计算b*/
        d2 = 0.0;

        for (j = 0; j < m; j++) {                      /* 计算Qi的函数值和d*/
            t = (y0[j] - a) * q1y[j] - b * q0y[j];
            q2y[j] = t;
            d2 = d2 + t * t;
        }

        for (k = 0; k < pp; k++) {                      /* 计算系数ukl*/
            t = 0.0;

            for (j = 0; j < m; j++) {
                t = t + q2y[j] * c[k * m + j];
            }

            u[k * qq + l] = t / d2;
        }

        l2 = l1 + qq;
        qy[l2] = -a * qy[l1] - b * qy[l0];             /* 计算Qi的系数*/
        qy[l2 + l] = 1.0;

        for (j = 1; j < l; j++) {
            qy[l2 + j] = qy[l1 + j - 1] - a * qy[l1 + j] - b * qy[l0 + j];
        }

        d0 = d1;
        d1 = d2;                              /* 循环使用变量*/
        l0 = l1;
        l1 = l2;

        for (j = 0; j < m; j++) {                      /* 循环使用数组*/
            q0y[j] = q1y[j];
            q1y[j] = q2y[j];
        }
    }

    for (k = 0; k < pp; k++)                         /* 计算多项式P(x,y)*/
        for (l = 0; l < qq; l++) {
            t = 0.0;

            for (i = k; i < pp; i++)
                for (j = l; j < qq; j++) {
                    t = t + u[i * qq + j] * qx[i * pp + k] * qy[j * qq + l];
                }

            p[k * qq + l] = t;
        }

    s[0] = 0.0;
    s[1] = 0.0;
    s[2] = 0.0;

    for (i = 0; i < n; i++) {
        x1 = x0[i];                                   /* 求P(xi, yj)*/

        for (j = 0; j < m; j++) {
            y1 = y0[j];
            t2 = 0;                                     /* 结果赋初值 */

            for (k = pp - 1; k >= 0; k--) {             /* 累次相加*/
                t = p[k * qq + qq - 1];

                for (l = qq - 2; l >= 0; l--) {
                    t = t * y1 + p[k * qq + l];
                }

                t2 = t2 * x1 + t;
            }                                           /* 此时t2=P(xi,yj)*/

            t2 = t2 - z[i * m + j];

            if (fabs(t2) > s[2]) {
                s[2] = fabs(t2);
            }

            s[0] = s[0] + t2 * t2;
            s[1] = s[1] + fabs(t2);
        }
    }

    free(x0);
    free(y0);                               /* 释放空间*/
    free(qx);
    free(qy);
    free(q0x);
    free(q1x);
    free(q2x);
    free(q0y);
    free(q1y);
    free(q2y);
    free(c);
    free(u);
    return (1);
}
