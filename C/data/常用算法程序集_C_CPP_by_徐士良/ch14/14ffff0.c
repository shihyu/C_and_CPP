
#include "stdio.h"
#include "14ffff.c"
main()
{
    int n1, n2, i;
    double y, f;
    int n[2] = { 2, 5};
    int m[2] = { 3, 10};
    printf("\n");

    for (i = 0; i <= 1; i++) {
        n1 = n[i];
        n2 = m[i];
        f = 3.5;
        y = ffff(f, n1, n2);
        printf("P(%4.2f, %d, %d)=%13.5e\n", f, n1, n2, y);
        f = 9.0;
        y = ffff(f, n1, n2);
        printf("P(%4.2f, %d, %d)=%13.5e\n", f, n1, n2, y);
    }

    printf("\n");
}

