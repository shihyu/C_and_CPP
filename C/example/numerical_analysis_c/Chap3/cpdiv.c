/*=============================================================
// 函 数 名：cpdiv(a,n,b,m,q,r)
// 功能描述：完成系数表示的复系数的多项式A与B相除
       商多项式系数放在q里，余式系数放在r里
// 输入参数：a（多项式A系数），n（系数个数）
       b（多项式B系数），m（系数个数）
       q（商多项式Q系数），k（系数个数）k=max(n-m+1,0)
       r（余式R系数），l（系数个数）需要l=n
// 返 回 值：整型数字。计算成功则返回1，否则返回0
//==============================================================*/
#include"stdio.h"
#include"c_comp.c"
int cpdiv(a, n, b, m, q, k, r, l)
struct c_comp* a, *b, *q, *r;
int n, m, k, l;
{
    int i, j, kk, jj;
    struct c_comp t1, t2;
    double tmp;

    if ((a == NULL) || (b == NULL) || (q == NULL) ||
        (r == NULL)) { /* 检测指针是否为空*/
        printf("(cpdiv)NULL pointer found.\n");
        return (0);
    }

    if (l != n) {
        printf("(cpdiv)please set the length of r to n.\n");
        return (0);
    }

    for (i = 0; i < n;
         i++) {               /* 先将a存入r中，这就是开始除法前的余式*/
        r[i].rmz = a[i].rmz;
        r[i].imz = a[i].imz;
    }

    for (i = 0; i < k; i++) {           /* 此时的商为0*/
        q[i].rmz = 0;
        q[i].imz = 0;
    }

    /* 判断多项式B最高次项系数是否为0*/
    tmp = b[m - 1].rmz * b[m - 1].rmz + b[m - 1].imz * b[m - 1].imz;

    if (tmp + 1.0 == 1.0) {
        printf("(cpdiv)Cannot divide zero");
        return (0);
    }

    b[m - 1].imz = -b[m -
                      1].imz;           /* 先取b[m-1]的共轭，将复数除法转化成乘法*/

    for (i = 0; i < k; i++) {
        kk = k - i - 1;
        jj = n - i - 1;
        c_comp_product(&r[jj], &b[m - 1], &t1);   /* 求出当前的商*/
        q[kk].rmz = t1.rmz / tmp;
        q[kk].imz = t1.imz / tmp;
        r[jj].rmz = 0.0;                      /* 从余式中减去当前的商与多项式B的积*/
        r[jj].imz = 0.0;

        for (j = 0; j < m - 1; j++) {
            c_comp_product(&q[kk], &b[j], &t2);
            c_comp_sub(&r[j + kk], &t2, &r[j + kk]);
        }
    }

    b[m - 1].imz = -b[m - 1].imz;           /* 恢复b[m-1]*/
    return (1);
}

