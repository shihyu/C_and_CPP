/*=============================================================
// 函 数 名：kabg (x,n,y)
// 功能描述：α-β-γ滤波算法
// 输入参数：x（输入数据），n（测量点个数）、y（滤波估值）
//           h （采样周期）
//          alfa（结构参数α），beta（结构参数β）、gama（结构参数γ）
// 返 回 值：无
//==============================================================*/
#include "stdio.h"
#include "math.h"
int kabg(x, n, y, h, alfa, beta, gama)
int n;
double* x, *y;
double h, alfa, beta, gama;
{
    int i;
    double a, v, z1, z, tmp, h2, invh2;
    a = 0.0;                                    /* 初始值设为零 */
    v = 0.0;
    z = 0.0;
    h2 = h * h;
    invh2 = 1.0 / h / h;

    for (i = 0; i < n; i++) {
        z1 = z + h * v + h2 * a * 0.5;           /* 中间值*/
        tmp = x[i] - z1;
        z = z1 + alfa * tmp;                     /* 第i次预测值*/
        y[i] = z;
        v = v + h * a +  beta * tmp;             /* 递推的中间变量v*/
        a = a + 0.5 * gama * tmp * invh2;        /* 递推的中间变量a*/
    }

    return (1);
}