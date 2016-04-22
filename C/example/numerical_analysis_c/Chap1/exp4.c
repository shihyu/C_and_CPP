#include "stdio.h"
#include "math.h"
void main()
{
    int n;
    double x;
    x = 0;
    printf("x30=%2.8e\n", x);

    for (n = 30; n > 0; n--) {
        x = 1.0 / 10.0 / n - x / 10.0;
        printf("x%2d=%e\n", n - 1, x);
    }
}
