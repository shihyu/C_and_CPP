
#include "stdio.h"
#include "14elp2.c"
main()
{
    int i;
    double f, k, y;
    printf("\n");

    for (i = 0; i <= 10; i++) {
        f = i * 3.1415926 / 18.0;
        k = 0.5;
        y = elp2(k, f);
        printf("E(%4.2f, %8.6f)=%13.5e    ", k, f, y);
        k = 1.0;
        y = elp2(k, f);
        printf("E(%4.2f, %8.6f)=%13.5e\n", k, f, y);
    }

    printf("\n");
}

