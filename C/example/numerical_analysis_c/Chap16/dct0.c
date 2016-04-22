#include "stdio.h"
#include "math.h"
#include "c_comp.c"
#include "fft.c"
#include "dct.c"

void main()
{
    int i;
    double a[4], b[4], y[4];

    for (i = 0; i < 4; i++) {                          /* 给定a和b*/
        a[i] = i + 1;
        b[i] = 2 * i;
    }

    printf(" a sequence\n");

    for (i = 0; i < 4; i++) {
        printf("%5.4f ", a[i]);
    }

    printf("\n b sequence\n");

    for (i = 0; i < 4; i++) {
        printf("%5.4f ", b[i]);
    }

    i = dct(a, 4, y);                                  /*求a的dctt*/

    if (i) {
        printf("\ndct of a:\n");

        for (i = 0; i < 4; i++) {
            printf("%5.4f ", y[i]);
        }
    }

    i = dct(b, 4, y);                                 /*求b的dctt*/

    if (i) {
        printf("\ndct of b:\n");

        for (i = 0; i < 4; i++) {
            printf("%5.4f ", y[i]);
        }
    }

    printf("\n");
}

