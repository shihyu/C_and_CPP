/*=============================================================
// 函 数 名：rpmva(a,n,x,m,y)
// 功能描述：利用多组求值方法求解一元多项式的值
// 输入参数：a（多项式系数），n（多项式阶次）
//        x（指定的值）,m（指定的值的个数）,y（返回的m个多项式值）
// 返 回 值：若成功则返回1,否则返回0
//==============================================================*/
#include"math.h"
#include"stdlib.h"

int rpmva(a, n, x, m, y)
int n, m;
double* a, *x, *y;
{
    int i, j, k, nn, nk, kk, l, count, tail;
    double* ax, *b;
    double a1, t1, t2;
    k = log(n - 0.5) / log(2.0) + 1; /* 求log2(k)*/
    nn = 1;

    for (i = 0; i < k; i++) {
        nn = nn << 1;
    }

    nk = nn >> 1;
    a1 = a[n - 1];      /* 检测首项系数是否为0，为0的话则返回。*/

    if (a1 + 1.0 == 1.0) {
        printf("(rpmva)coefficient too small,please check.\n");
        return (0);
    }

    /* b用来存放系数分解的中间结果，ax用来存放迭代计算的结果*/
    b = (double*)malloc(nn * sizeof(double));
    ax = (double*)malloc(nk * sizeof(double));

    for (i = 0; i < n; i++) { /* 系数首1化*/
        b[i] = a[i] / a1;
    }

    for (i = n; i < nn; i++) {
        b[i] = 0.0;
    }

    l = nn >> 1;        /* l是每次分段的长度，count是分段的总个数的一半*/
    count = 1;

    for (i = 1; i < k; i++) {
        /*  此是tail指向第一段的尾部，也就是多项式A1(x)的开头位置。
         *  注意多项式系数是从低阶向高阶依次存储的*/
        tail = l - 1;

        for (j = 0; j < count; j++) {
            b[tail] = b[tail] - 1.0; /* 这个要减去1的值，就是我们算法说明里每次分解时的b*/

            for (kk = 1; kk < l; kk++) { /* 使用这个循环完成了算法说明里的A0 = A0-b*A1*/
                b[tail - kk] = b[tail - kk] - b[tail] * b[tail - kk + l];
            }

            tail = tail + 2 * l;    /* tail指向下一个奇数段的尾部*/
        }

        l = l >> 1;           /* 每段的长度减半*/
        count = count << 1;       /* 分段的总数增加一倍*/
    }

    for (kk = 0; kk < m; kk++) {
        t1 = x[kk];

        /* 第一次迭代，相加的结果存入ax中。
        * 这里完成了分解得到的一次多项式的运算*/
        for (i = 0; i < nk; i++) {
            ax[i] = t1 + b[2 * i];
        }

        /* 以下的代码开始沿系数分解的逆顺序回推
        * 分解后的多项式两两成对，记为A0和A1*/

        tail = 1;                /* 则ax[j]指向的是A0的求值结果，ax[j+tail]指向的是A1的求值结果*/
        l = 2;                   /* l的初始值是2*/
        t2 = t1;                 /* t2是就是待求值的x*/

        /* 合并k-1次，完成求值
        * 每次合并需要的b值从b中对应位置寻找
        * 每两段合并的结果都放在这两段最前面的位置
        * 这样最后的结果存放在ax[0]中*/
        for (i = 1; i < k; i++) {
            t2 = t2 * t2;          /* 每次组合新一级的多项式对时，x都会变为原来的平方*/

            /* 将所有本级的多项式对进行组合*/
            for (j = 0; j < nk; j = j + l) {
                ax[j] = ax[j] + ax[j + tail] * (t2 + b[2 * (j + tail) - 1]);
            }

            tail = tail << 1;      /* 现在的多项式长度变为之前的两倍了*/
            l = l << 1;            /* 现在的多项式长度变为之前的两倍了*/
        }

        t2 = t2 * t2 / t1;       /* 消除b[nn-1]=1的影响*/

        if (nn != n) {
            ax[0] -= t2;
        }

        y[kk] = ax[0] * a1;      /* 消除系数首1化带来的影响*/
    }

    free(b);
    free(ax);
    return (1);
}
