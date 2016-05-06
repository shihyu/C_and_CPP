
#include "stdio.h"
#include "1cpdv.c"
main()
{
    int i;
    double pr[5] = {8.0, -5.0, -3.0, 6.0, 3.0};
    double pi[5] = {3.0, 4.0, 4.0, -5.0, -1.0};
    double qr[3] = {1.0, -1.0, 2.0};
    double qi[3] = {2.0, -3.0, 2.0};
    double sr[3], si[3], rr[2], ri[2];
    cpdv(pr, pi, 5, qr, qi, 3, sr, si, 3, rr, ri, 2);
    printf("\n");

    for (i = 0; i <= 2; i++) {
        printf(" s(%d)=%13.6e +j %13.6e\n", i, sr[i], si[i]);
    }

    printf("\n");

    for (i = 0; i <= 1; i++) {
        printf(" r(%d)=%13.6e +j %13.6e\n", i, rr[i], ri[i]);
    }

    printf("\n");
}

