#include "stdio.h"
#include "math.h"
void main()
{
    int n;
    double x;
    x = log(11.0 / 10.0);
    printf("x 0=%e\n", x);

    for (n = 1; n < 21; n++) {
        x = 1.0 / n - 10 * x;
        printf("x%2d=%e\n", n, x);
    }
}
