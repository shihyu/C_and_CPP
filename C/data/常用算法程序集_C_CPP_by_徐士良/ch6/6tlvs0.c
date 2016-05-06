
#include "stdio.h"
#include "6tlvs.c"
main()
{
    int i;
    double x[6];
    double t[6] = {6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    double b[6] = {11.0, 9.0, 9.0, 9.0, 13.0, 17.0};

    if (tlvs(t, 6, b, x) > 0)
        for (i = 0; i <= 5; i++) {
            printf("x(%d)=%13.6e\n", i, x[i]);
        }
}

