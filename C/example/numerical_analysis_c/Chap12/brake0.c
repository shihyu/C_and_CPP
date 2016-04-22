#include "stdio.h"
#include "math.h"
#include "brake.c"
#include "bsl1.c"

void main()
{
    double a, b, c, fa, fb, fc;
    double f(double);
    int i;

    for (i = 1; i < 10; i++) {
        a = i * 0.5;
        b = (i + 1) * 0.5;
        brake(&a, &b, &c, f);
        fa = f(a);
        fb = f(b);
        fc = f(c);
        printf("  a         b         c\n");
        printf("x %5.4f %5.4f %5.4f\n", a, b, c);
        printf("f %5.4f %5.4f %5.4f\n", fa, fb, fc);
    }
}

double f(double x)
{
    return bsl1(0, x);
}