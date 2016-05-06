
#include "stdio.h"
#include "6trde.c"
main()
{
    int i;
    double b[13] = {13.0, 12.0, 11.0, 10.0, 9.0, 8.0, 7.0,
                    6.0, 5.0, 4.0, 3.0, 2.0, 1.0
                   };
    double d[5] = {3.0, 0.0, -2.0, 6.0, 8.0};

    if (trde(b, 5, 13, d) > 0)
        for (i = 0; i <= 4; i++) {
            printf("x(%d)=%13.6e\n", i, d[i]);
        }
}

