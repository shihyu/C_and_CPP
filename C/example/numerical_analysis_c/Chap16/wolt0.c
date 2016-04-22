#include "stdio.h"
#include "math.h"
#include "wolt.c"
#include "hadma.c"

void main()
{
    int i, n = 8;
    double a[8], b[8], y[8];

    for (i = 0; i < n; i++) {                          /* 给定a和b*/
        a[i] = i + 1;
        b[i] = 2 * i;
    }

    printf(" a sequence\n");

    for (i = 0; i < n; i++) {
        printf("%5.4f ", a[i]);
    }

    printf("\n b sequence\n");

    for (i = 0; i < n; i++) {
        printf("%5.4f ", b[i]);
    }

    i = wolt(a, n, y);                                 /*求a的wolt变换*/

    if (i) {
        printf("\n\nwolt of a:\n");

        for (i = 0; i < n; i++) {
            printf("%5.4f ", y[i]);
        }
    }

    i = wolt(y, n, a);                                 /* wolt逆变换*/

    if (i) {
        printf("\nwolt of wolt(a):\n");

        for (i = 0; i < n; i++) {
            printf("%5.4f ", a[i]);
        }
    }

    i = wolt(b, n, y);                                /* 求b的wolt变换*/

    if (i) {
        printf("\nwolt of b:\n");

        for (i = 0; i < n; i++) {
            printf("%5.4f ", y[i]);
        }
    }

    i = wolt(y, n, b);                                 /*wolt逆变换*/

    if (i) {
        printf("\nwolt of wolt(b):\n");

        for (i = 0; i < n; i++) {
            printf("%5.4f ", b[i]);
        }
    }

    i = hadma(a, n, y);                                    /*求a的哈达玛变换*/

    if (i) {
        printf("\n\nhadma of a:\n");

        for (i = 0; i < n; i++) {
            printf("%5.4f ", y[i]);
        }
    }

    i = hadma(y, n, a);                                   /*哈达玛逆变换*/

    if (i) {
        printf("\nhadma of hadma(a):\n");

        for (i = 0; i < n; i++) {
            printf("%5.4f ", a[i]);
        }
    }

    i = hadma(b, n, y);                                   /*求b的哈达玛变换*/

    if (i) {
        printf("\nhadma of b:\n");

        for (i = 0; i < n; i++) {
            printf("%5.4f ", y[i]);
        }
    }

    i = hadma(y, n, b);                                   /*哈达玛逆变换*/

    if (i) {
        printf("\nhadma of hadma(b):\n");

        for (i = 0; i < n; i++) {
            printf("%5.4f ", b[i]);
        }
    }

    printf("\n");
}

