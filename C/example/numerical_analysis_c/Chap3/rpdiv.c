/*=============================================================
// 函 数 名：rpdiv(a,n,b,m,q,r)
// 功能描述：完成系数表示的实系数的多项式A与B相除
       商多项式系数放在q里，余式系数放在r里
// 输入参数：a（多项式A系数），n（系数个数）
       b（多项式B系数），m（系数个数）
       q（商多项式Q系数），k（系数个数）k=max(n-m+1,0)
       r（余式R系数），l（系数个数）需要l=n
// 返 回 值：整型数字。计算成功则返回1，否则返回0
//==============================================================*/
#include"stdio.h"
int rpdiv(a, n, b, m, q, k, r, l)
double* a, *b, *q, *r;
int n, m, k, l;
{
    int i, j, kk, jj;

    if ((a == NULL) || (b == NULL) || (q == NULL) ||
        (r == NULL)) { /* 检测指针是否为空*/
        printf("(rpdiv)NULL pointer found.\n");
        return (0);
    }

    if (l != n) {             /* 检测余式的空间是否足够*/
        printf("(rpdiv)please set the length of r to n.\n");
        return (0);
    }

    for (i = 0; i < n; i++) {         /* 初始化余式和商*/
        r[i] = a[i];
    }

    for (i = 0; i < k; i++) {
        q[i] = 0.0;
    }

    if (b[m - 1] + 1.0 ==
        1.0) {      /* 检测除式的首项系数，若其几乎为0，函数结束。*/
        printf("(rpdiv)Cannot divide zero");
        return (0);
    }

    for (i = 0; i < k; i++) {
        kk = k - i - 1;
        jj = n - i - 1;
        q[kk] = r[jj] / b[m - 1];           /* 计算当前商*/
        r[jj] = 0.0;                /* 从余式中减去当前商与多项式B的乘积*/

        for (j = 0; j < m - 1; j++) {
            r[j + kk] -= q[kk] * b[j];
        }
    }

    return (1);
}

