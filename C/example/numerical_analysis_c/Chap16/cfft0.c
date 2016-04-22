#include "stdio.h"
#include "math.h"
#include "c_comp.c"
#include "fft.c"
#include "ifft.c"
#include "r2fft.c"

void main()
{
    int i;
    struct c_comp x[4], y[4], y1[4], y2[4];
    double a[4], b[4];

    for (i = 0; i < 4; i++) {                          /* 给定a和b*/
        a[i] = i + 1;
        b[i] = 2 * i;
    }

    printf(" a sequence\n");

    for (i = 0; i < 4; i++) {
        printf("%3.1f ", a[i]);
    }

    printf("\n b sequence\n");

    for (i = 0; i < 4; i++) {
        printf("%3.1f ", b[i]);
    }

    for (i = 0; i < 4; i++) {
        x[i].rmz = a[i];
        x[i].imz = 0;
    }

    i = fft(x, 4, y);                                  /*求a的fft*/

    if (i) {
        printf("\n\nfft of a:\n");

        for (i = 0; i < 4; i++) {
            printf("%3.1f+i*%3.1f ", y[i].rmz, y[i].imz);
        }
    }

    for (i = 0; i < 4; i++) {
        x[i].rmz = b[i];
        x[i].imz = 0;
    }

    i = fft(x, 4, y);                                 /*求b的fft*/

    if (i) {
        printf("\nfft of b:\n");

        for (i = 0; i < 4; i++) {
            printf("%3.1f+i*%3.1f ", y[i].rmz, y[i].imz);
        }
    }

    r2fft(a, b, 4, y1, y2);                           /* 对两个实序列同时求fft*/
    printf("\n\nr2fft:\n");
    printf("fft of a:\n");

    for (i = 0; i < 4; i++) {
        printf("%3.1f+i*%3.1f ", y1[i].rmz, y1[i].imz);
    }

    printf("\nfft of b:\n");

    for (i = 0; i < 4; i++) {
        printf("%3.1f+i*%3.1f ", y2[i].rmz, y2[i].imz);
    }

    i = ifft(y1, 4, x);                               /*求fft(a)的ifft*/

    if (i) {
        printf("\n\nifft of fft(b):\n");

        for (i = 0; i < 4; i++) {
            printf("%3.1f+i*%3.1f ", x[i].rmz, x[i].imz);
        }
    }

    i = ifft(y2, 4, x);                               /*求fft(b)的ifft*/

    if (i) {
        printf("\nifft of fft(b):\n");

        for (i = 0; i < 4; i++) {
            printf("%3.1f+i*%3.1f ", x[i].rmz, x[i].imz);
        }
    }

    printf("\n");
}

