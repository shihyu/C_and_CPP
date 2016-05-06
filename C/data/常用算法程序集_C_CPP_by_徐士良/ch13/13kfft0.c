
#include "stdio.h"
#include "13kfft.c"
#include "math.h"
main()
{
    int i, j;
    double pr[64], pi[64], fr[64], fi[64];

    for (i = 0; i <= 63; i++) {
        pr[i] = exp(-0.1 * (i + 0.5));
        pi[i] = 0.0;
    }

    printf("\n");

    for (i = 0; i <= 15; i++) {
        for (j = 0; j <= 3; j++) {
            printf("%13.5e   ", pr[4 * i + j]);
        }

        printf("\n");
    }

    printf("\n");
    kfft(pr, pi, 64, 6, fr, fi, 0, 1);

    for (i = 0; i <= 15; i++) {
        for (j = 0; j <= 3; j++) {
            printf("%13.5e   ", fr[4 * i + j]);
        }

        printf("\n");
    }

    printf("\n");

    for (i = 0; i <= 15; i++) {
        for (j = 0; j <= 3; j++) {
            printf("%13.5e   ", fi[4 * i + j]);
        }

        printf("\n");
    }

    printf("\n");

    for (i = 0; i <= 15; i++) {
        for (j = 0; j <= 3; j++) {
            printf("%13.5e   ", pr[4 * i + j]);
        }

        printf("\n");
    }

    printf("\n");

    for (i = 0; i <= 15; i++) {
        for (j = 0; j <= 3; j++) {
            printf("%13.5e   ", pi[4 * i + j]);
        }

        printf("\n");
    }

    printf("\n");
    kfft(fr, fi, 64, 6, pr, pi, 1, 1);

    for (i = 0; i <= 15; i++) {
        for (j = 0; j <= 3; j++) {
            printf("%13.5e   ", fr[4 * i + j]);
        }

        printf("\n");
    }

    printf("\n");
}

