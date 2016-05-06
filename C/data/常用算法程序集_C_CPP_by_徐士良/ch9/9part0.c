
#include "9part.c"
#include "stdio.h"
main()
{
    int n, m;
    double a, b;
    double s[2], fa[4] = {0.0, 1.0, 0.0, -3.0};
    double fb[4] = {6.2831852, 1.0, -6.2831852, -3.0};
    a = 0.0;
    b = 6.2831852;
    m = 30;
    n = 4;
    part(a, b, m, n, fa, fb, s);
    printf("\n");
    printf("s(0)=%13.5e ,   s(1)=%13.5e\n", s[0], s[1]);
    printf("\n");
}

