#include "math.h"
/*======================================================
// 函数名：gasi
// 功能描述：自适应高斯求积分
// 输入参数：a 积分下限，b 积分上限,
//           eps 精度要求
//           nmax 最大迭代次数
//           f 指向被积函数的指针
// 返回值：  积分近似值
=========================================================*/
double gasi(a, b, eps, nmax, f)
double a, b, eps;
int nmax;
double (*f)();
{
    double z, z1, z2;
    double subleg(), sublagr(), subhemt();  /* 声明要调用的三个子函数*/

    if ((a < -1.0e34) && (b > 1.0e34)) {     /* 此区间为无限区间(-inf,inf)*/
        z = subhemt(f);
    } else if ((a < -1.0e34) && (b < 0)) {   /* 此区间为半无限区间(-inf,b),b<0*/
        z1 = sublagr(b - 1.0, 0.0, eps, nmax, f, -1);
        z2 = subleg(b - 1.0, b, 0.0, eps, nmax, f);
        z = z1 + z2;
    } else if (a < -1.0e34) {                /* 此区间为半无限区间(-inf,b),b>=0*/
        z1 = sublagr(-b - 1.0, 0.0, eps, nmax, f, -1);
        z2 = subleg(-b - 1.0, b, 0.0, eps, nmax, f);
        z = z1 + z2;
    } else if ((a < 0) && (b > 1.0e34)) {    /* 此区间为半无限区间(a,inf),a<0*/
        z1 = sublagr(-a + 1.0, 0.0, eps, nmax, f, 1);
        z2 = subleg(a, -a + 1.0, 0.0, eps, nmax, f);
        z = z1 + z2;
    } else if (b > 1.0e34) {                 /* 此区间为半无限区间(a,inf),a>=0*/
        z1 = sublagr(a + 1.0, 0.0, eps, nmax, f, 1);
        z2 = subleg(a, a + 1.0, 0.0, eps, nmax, f);
        z = z1 + z2;
    } else {                                 /* 此区间为有限区间(a,b)*/
        z = subleg(a, b, 0.0, eps, nmax, f);
    }

    return (z);
}

static double subleg(x0, x1, z0, eps, n0, f)
double x0, x1, z0, eps;
int n0;
double (*f)();
{
    int j;
    double x, z1, z2, d, z, h;
    static double tg[5] = { -0.906179845938664, -0.538469310105683, 0.0,
                            0.538469310105683, 0.906179845938664
                          }; /* 5阶勒让德多项式的零点*/
    static double cg[5] = {0.236926885056189, 0.478628670499366,
                           0.568888888888888, 0.478628670499366,
                           0.236926885056189
                          };    /* 使用5阶勒让德多项式时的参数*/
    h = (x1 - x0) / 2.0;
    z1 = 0.0;
    x = x0 + h / 2.0;

    for (j = 0; j < 5; j++) {
        z1 = z1 + cg[j] * (*f)(h / 2.0 * tg[j] + x);
    }

    z1 = z1 * h / 2.0;                   /* 第一个子区间的积分近似值*/

    z2 = 0.0;
    x = x0 + 3.0 * h / 2.0;

    for (j = 0; j < 5; j++) {
        z2 = z2 + cg[j] * (*f)(h / 2.0 * tg[j] + x);
    }

    z2 = z2 * h / 2.0;                   /* 第二个子区间的积分近似值*/
    d = fabs(z0 - (z1 + z2));

    if ((d < eps) || (n0 < 0)) {
        z = z1 + z2;    /* 已经满足精度要求或不允许继续划分*/
    } else {
        z1 = subleg(x0, x0 + h, z1, eps / 1.4, n0 - 1, f);
        z2 = subleg(x0 + h, x1, z2, eps / 1.4, n0 - 1, f);
        z = z1 + z2;                           /* 返回两个子区间的积分近似值之和*/
    }

    return (z);
}

static double sublagr(x0, z0, eps, n0, f, p)
double x0, z0, eps;
int n0, p;
double (*f)();
{
    int j;
    double x, z1, z2, d, h;
    double z;                                         /* 5阶拉盖尔多项式的零点*/
    static double tr[5] = {0.2635608366230711, 1.413402992130087,
                           3.5964257647443034, 7.08581000836623, 12.640800845980232
                          };
    static double cr[5] = {0.679094868860246, 1.638485827229450,
                           2.769447700914552, 4.315635380726091, 7.219514571190223
                          };
    static double tg[5] = { -0.906179845938664, -0.538469310105683, 0.0,
                            0.538469310105683, 0.906179845938664
                          }; /* 5阶勒让德多项式的零点*/
    static double cg[5] = {0.236926885056189, 0.478628670499366,
                           0.568888888888888, 0.478628670499366,
                           0.236926885056189
                          };    /* 使用5阶勒让德多项式时的参数*/
    z1 = 0.0;
    z2 = 0.0;

    if (p < 0) {                             /* 此时x0<0*/
        h = -x0 / 2.0;
        x = x0 - h;

        for (j = 0; j < 5; j++) {
            z1 = z1 + cg[j] * (*f)(h * tg[j] + x);
        }

        z1 = z1 * h;                           /* 子区间(2x0,x0)的积分近似值*/

        for (j = 0; j < 5; j++) {
            z2 = z2 + cr[j] * (*f)(x0 + x0 - tr[j]);    /* 子区间(-inf,2x0)的积分近似值*/
        }

        d = fabs(z0 - (z1 + z2));
    } else {                                 /* 此时x0>0*/
        h = x0 / 2.0;
        x = x0 + h;

        for (j = 0; j < 5; j++) {
            z1 = z1 + cg[j] * (*f)(h * tg[j] + x);
        }

        z1 = z1 * h;                           /* 子区间(x0,2x0)的积分近似值*/

        for (j = 0; j < 5; j++) {
            z2 = z2 + cr[j] * (*f)(x0 + x0 + tr[j]);    /* 子区间(2x0,inf)的积分近似值*/
        }

        d = fabs(z0 - (z1 + z2));
    }

    z = z1 + z2;

    if (fabs(z) > 1.0e34) {
        n0 = 0;
    } else if ((d > eps) && (n0 > 1)) {           /* 不满足精度就继续划分*/
        /* 划分为一个有限区间和一个半无限区间*/
        if (p == 1) {
            z1 = subleg(x0, x0 + x0, z1, eps / 1.4, n0 - 1, f);
        } else {
            z1 = subleg(x0 + x0, x0, z1, eps / 1.4, n0 - 1, f);
        }

        z2 = sublagr(x0 + x0, z2, eps / 1.4, n0 - 1, f, p);
        z = z1 + z2;                              /* 返回两个子区间的积分近似值之和*/
    }

    return (z);
}

static double subhemt(f)
double (*f)();
{
    int j;
    double z;                                   /* 5阶埃尔米特多项式的零点*/
    static double tt[5] = { -2.020182496984754, -0.9585724979524882, 0.0,
                            0.9585724979524882, 2.020182496984754
                          };
    static double ct[5] = {1.181487737274476, 0.986580905130196,
                           0.945308813693166, 0.986580905130196, 1.181487737274476
                          };
    z = 0.0;

    for (j = 0; j < 5; j++) {                    /* 求解积分值*/
        z = z + ct[j] * (*f)(tt[j]);
    }

    return (z);
}
