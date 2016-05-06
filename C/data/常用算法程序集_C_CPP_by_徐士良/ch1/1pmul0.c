
#include "stdio.h"
#include "1pmul.c"
main()
{
    int i;
    double p[6] = {4.0, -6.0, 5.0, 2.0, -1.0, 3.0};
    double q[4] = {2.0, 3.0, -6.0, 2.0};
    double s[9];
    pmul(p, 6, q, 4, s, 9);
    printf("\n");

    for (i = 0; i <= 8; i++) {
        printf(" s(%d)=%13.7e\n", i, s[i]);
    }

    printf("\n");
}

