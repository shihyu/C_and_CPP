#include "math.h"
#include "stdio.h"
#include "frac.c"
main()
{
    int nmax;
    double f, e0, e1;
    void fab();
    nmax = 100;
    e1 = 1.0e-7;
    e0 = 1.0e-30;
    f = frac(fab, nmax, e1, e0);
    printf("f=%e\n", f);        /* 打印结果*/
    getchar();
}

void fab(j, ab)               /* 计算系数的函数*/
int j;
double* ab;
{
    double a = 0.5, x = 2.5;    /* 两个参数*/

    if (j == 0) {               /*b0= 0，此时的a0不重要*/
        ab[0] = 0.0;
        ab[1] = 0.0;
    } else if (j == 1) {        /* a1 和 b1*/
        ab[0] = 1.0;
        ab[1] = x + 1.0 - a;
    } else {                    /* aj 和 bj*/
        ab[0] = (j - 1) * (a - j + 1.0);
        ab[1] = x + 2.0 * j + 1.0 - a;
    }

    return;
}
