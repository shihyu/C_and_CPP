#include"stdio.h"
#include"math.h"
#include"c_comp.c"
#include "cpmul.c"
#include "cpdiv.c"
void main()
{
    int i;
    struct c_comp a[3], b[3], c[5], q[4], r[5];

    for (i = 0; i < 3; i++) {
        a[i].rmz = i + 1;
        a[i].imz = 2 * i + 1;
        b[i].rmz = i;
        b[i].imz = i + 1;
    }

    i = cpmul(a, 3, b, 3, c);     /* 调用多项式相乘的函数，并打印结果*/

    if (i) {
        printf("c=a*b:\n");

        for (i = 0; i < 5; i++) {
            printf("c[%d]=%2.1f+i*(%2.1f)\n", i, c[i].rmz, c[i].imz);
        }
    }

    i = cpdiv(c, 5, b, 3, q, 3, r, 5); /* 调用多项式相除的函数，并打印结果*/

    if (i) {
        printf("c/b--Q:\n");

        for (i = 0; i < 3; i++) {
            printf("q[%d]=%2.1f+i*(%2.1f) ", i, q[i].rmz, q[i].imz);
        }

        printf("\nc/b--R:\n");

        for (i = 0; i < 5; i++) {
            printf("r[%i]=%2.1f+i*(%2.1f)\n", i, r[i].rmz, r[i].imz);
        }
    }
}
