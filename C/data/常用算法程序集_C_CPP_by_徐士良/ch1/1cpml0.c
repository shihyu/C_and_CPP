
#include "stdio.h"
#include "1cpml.c"
main()
{
    int i;
    double pr[6] = {4.0, -6.0, 5.0, 2.0, -1.0, 3.0};
    double pi[6] = {2.0, 3.0, -4.0, 1.0, -1.0, 2.0};
    double qr[4] = {2.0, 3.0, -6.0, 2.0};
    double qi[4] = {1.0, 2.0, -4.0, 1.0};
    double sr[9], si[9];
    cpml(pr, pi, 6, qr, qi, 4, sr, si, 9);
    printf("\n");

    for (i = 0; i <= 8; i++) {
        printf(" s(%d)=%13.6e +j %13.6e\n", i, sr[i], si[i]);
    }

    printf("\n");
}

