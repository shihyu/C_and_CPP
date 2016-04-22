#ifndef C_COMP_H
#define C_COMP_H

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define PI 3.1415926

struct c_comp {
    double rmz;
    double imz;
};

int c_comp_plus(a1, a2, c)
struct c_comp* a1, *a2, *c;
{
    if (a1 == NULL || a2 == NULL || c == NULL) {
        printf("(c_comp_plus)The c_comp pointer is NULL!\n");
        return (0);
    }

    c->rmz = a1->rmz + a2->rmz;
    c->imz = a1->imz + a2->imz;
    return (1);
}

int c_comp_product(a1, a2, c)
struct c_comp* a1, *a2, *c;
{
    double p, q, s;

    if (a1 == NULL || a2 == NULL || c == NULL) {
        printf("(c_comp_product)The c_comp pointer is NULL!\n");
        return (0);
    }

    p = a1->rmz * a2->rmz;
    q = a1->imz * a2->imz;
    s = (a1->rmz + a1->imz) * (a2->rmz + a2->imz);
    c->rmz = p - q;
    c->imz = s - p - q;
    return (1);
}


int c_comp_divide(a1, a2, c)
struct c_comp* a1, *a2, *c;
{
    double R2;

    if (a1 == NULL || a2 == NULL || c == NULL) {
        printf("(c_comp_divide)The c_comp pointer is NULL!\n");
        return (0);
    }

    R2 = a2->rmz * a2->rmz + a2->imz * a2->imz;
    c_comp_product(&a1, &a2, &c);
    c->rmz = c->rmz / R2;
    c->imz = c->imz / R2;

    return (1);
}


int c_comp_power(a, c, n)
struct c_comp* a, *c;
int n;
{
    double R, theta;

    if (a == NULL || c == NULL) {
        printf("(c_comp_power)The c_comp pointer is NULL!\n");
        return (0);
    }

    theta = atan2(a->imz, a->rmz);
    R = sqrt(a->rmz * a->rmz + a->imz * a->imz);

    theta = n * theta;
    R = pow(R, n);

    c->rmz = R * cos(theta);
    c->imz = R * sin(theta);
    return (1);
}

int c_comp_nthroot(a, c, n)
struct c_comp* a, *c;
int n;
{
    int i;
    double R, theta;

    if (a == NULL || c == NULL) {
        printf("(c_comp_nthroot)The c_comp pointer is NULL!\n");
        return (0);
    }

    theta = atan2(a->imz, a->rmz);
    R = sqrt(a->rmz * a->rmz + a->imz * a->imz);

    R = pow(R, 1.0 / n);

    for (i = 0; i < n; i++) {
        c[i].rmz = R * cos((theta + 2 * i * PI) / n);
        c[i].imz = R * sin((theta + 2 * i * PI) / n);
    }

    return (1);
}


int c_comp_exp(a, c)
struct c_comp* a, *c;
{
    double R;

    if (a == NULL || c == NULL) {
        printf("(c_comp_exp)The c_comp pointer is NULL!\n");
        return (0);
    }

    R = exp(a->rmz);

    c->rmz = R * cos(a->imz);
    c->imz = R * sin(a->imz);

    return (1);
}

int c_comp_log(a, c)
struct c_comp* a, *c;
{

    if (a == NULL || c == NULL) {
        printf("(c_comp_log)The c_comp pointer is NULL!\n");
        return (0);
    }

    c->rmz = log(sqrt(a->rmz * a->rmz + a->imz * a->imz));
    c->imz = atan2(a->imz, a->rmz);

    return (1);
}


int c_comp_sin(a, c)
struct c_comp* a, *c;
{
    double tmp1, tmp2;

    if (a == NULL || c == NULL) {
        printf("(c_comp_sin)The c_comp pointer is NULL!\n");
        return (0);
    }

    tmp1 = exp(a->imz);
    tmp2 = exp(-a->imz);
    c->rmz = sin(a->rmz) * (tmp1 + tmp2) / 2;
    c->imz = cos(a->rmz) * (tmp1 - tmp2) / 2;

    return (1);
}

int c_comp_cos(a, c)
struct c_comp* a, *c;
{
    double tmp1, tmp2;

    if (a == NULL || c == NULL) {
        printf("(c_comp_cos)The c_comp pointer is NULL!\n");
        return (0);
    }

    tmp1 = exp(a->imz);
    tmp2 = exp(-a->imz);
    c->rmz = cos(a->rmz) * (tmp1 + tmp2) / 2;
    c->imz = -sin(a->rmz) * (tmp1 - tmp2) / 2;

    return (1);
}

#endif










