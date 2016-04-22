/*=============================================================
// 函 数 名：cpmul(a,n,b,m,c)
// 功能描述：完成系数表示的复系数的多项式A与B相乘，结果系数放在c里
// 输入参数：a（多项式A系数），n（系数个数）
         b（多项式B系数），m（系数个数）
         c（返回的多项式C的系数）
// 返 回 值：整型数字。计算成功则返回1，否则返回0
//==============================================================*/

#include"stdio.h"
#include"math.h"
#include"c_comp.c"  /*复系数多项式的乘法函数需要调用系数和点表示相互转化的两个函数*/
#include"p2c.c"
#include"c2p.c"

int cpmul(a, n, b, m, c)
struct c_comp* a, *b, *c;
int n, m;
{
    int i, k, nn;
    struct c_comp* aa, *bb, *cc, *ya, *yb, *yc;

    if ((a == NULL) || (b == NULL) || (c == NULL)) { /* 检测是否有指针为空*/
        printf("(cpmul)NULL pointer found.\n");
        return (0);
    }

    k = log(n + m - 1 - 0.5) / log(2.0) +
        1; /* 求最小的k，并满足2^k 不小于多项式C的阶数*/
    nn = 1;               /* 求出2^k*/

    for (i = 0; i < k; i++) {
        nn = nn << 1;
    }

    /* 为扩展后的多项式分配足够的空间*/
    aa = (struct c_comp*)malloc(nn * sizeof(struct c_comp));
    bb = (struct c_comp*)malloc(nn * sizeof(struct c_comp));
    cc = (struct c_comp*)malloc(nn * sizeof(struct c_comp));
    ya = (struct c_comp*)malloc(nn * sizeof(struct c_comp));
    yb = (struct c_comp*)malloc(nn * sizeof(struct c_comp));
    yc = (struct c_comp*)malloc(nn * sizeof(struct c_comp));

    if (!(aa && bb && cc && ya && yb && yc)) { /* 检测是否有指针为空*/
        printf("(cpmul)memory alloc failed.\n");
        return (0);
    }

    for (i = 0; i < n;
         i++) {      /*将A,B两个多项式补足成2^k阶的，并转存在aa与bb中*/
        aa[i].rmz = a[i].rmz;
        aa[i].imz = a[i].imz;
    }

    for (i = n; i < nn; i++) {
        aa[i].rmz = 0;
        aa[i].imz = 0;
    }

    for (i = 0; i < m; i++) {
        bb[i].rmz = b[i].rmz;
        bb[i].imz = b[i].imz;
    }

    for (i = m; i < nn; i++) {
        bb[i].rmz = 0;
        bb[i].imz = 0;
    }

    i = c2p(aa, nn, ya);           /*求出扩展后多项式A的点表示形式*/
    k = c2p(bb, nn, yb);           /*求出扩展后多项式B的点表示形式*/

    if (i && k) {          /* 若点表示求解成功，继续运算。否则返回0*/

        for (i = 0; i < nn; i++) {   /* 计算在各点上的乘积*/
            c_comp_product(&ya[i], &yb[i], &yc[i]);
        }

        k = p2c(yc, nn, cc);         /*求出多项式C的系数*/

        if (k) {             /*剔除多余的高阶零项。若p2c函数失败，则返回0*/
            for (i = 0; i < m + n - 1; i++) {
                c[i].rmz = cc[i].rmz;
                c[i].imz = cc[i].imz;
            }

            return (1);
        } else {
            return (0);
        }
    } else {
        return (0);
    }
}
