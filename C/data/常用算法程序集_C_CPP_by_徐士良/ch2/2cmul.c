
void cmul(a, b, c, d, u, v)
double a, b, c, d, *u, *v;
{
    double p, q, s;
    p = a * c;
    q = b * d;
    s = (a + b) * (c + d);
    *u = p - q;
    *v = s - p - q;
    return;
}

