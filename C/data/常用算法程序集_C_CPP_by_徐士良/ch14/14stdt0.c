
#include "stdio.h"
#include "14stdt.c"
main()
{
    int n;
    double t, y;
    printf("\n");

    for (n = 1; n <= 5; n++) {
        t = 0.5;
        y = stdt(t, n);
        printf("P(%4.2f, %d)=%13.5e\n", t, n, y);
        t = 5.0;
        y = stdt(t, n);
        printf("P(%4.2f, %d)=%13.5e\n", t, n, y);
    }

    printf("\n");
}

