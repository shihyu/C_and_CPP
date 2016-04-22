#include "stdio.h"
#include "math.h"
#include "c_comp.c"
#include "c2p.c"
#include "p2c.c"

void main()
{
    int i;
    struct c_comp a[4], y[4], b[4];

    for (i = 0; i < 4; i++) {
        a[i].rmz = i + 1;
        a[i].imz = 0;
    }

    i = c2p(a, 4, y);  /*调用系数表示转化为点表示的函数，并打印*/

    if (i) {
        printf("c2p:\n");

        for (i = 0; i < 4; i++) {
            printf("%f+i*%f\n", y[i].rmz, y[i].imz);
        }
    }

    i = p2c(y, 4, b); /*调用点表示转化为系数表示的函数，并打印*/

    if (i) {
        printf("p2c:\n");

        for (i = 0; i < 4; i++) {
            printf("%f+i*%f\n", b[i].rmz, b[i].imz);
        }
    }
}

