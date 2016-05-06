
#include "stdio.h"
#include "8lg3.c"
main()
{
    double t, z;
    double x[5] = {1.615, 1.634, 1.702, 1.828, 1.921};
    double y[5] = {2.41450, 2.46459, 2.65271, 3.03035, 3.34066};
    printf("\n");
    t = 1.682;
    z = lg3(x, y, 5, t);
    printf("x=%6.3f,   f(x)=%13.5e\n", t, z);
    t = 1.813;
    z = lg3(x, y, 5, t);
    printf("x=%6.3f,   f(x)=%13.5e\n", t, z);
    printf("\n");
}

