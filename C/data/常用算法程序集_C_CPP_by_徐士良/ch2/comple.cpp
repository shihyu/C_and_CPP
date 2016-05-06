//COMPLEX.CPP
//复数运算
#include  <iostream.h>
#include  <iomanip.h>
#include  <fstream.h>
#include  <math.h>
//  using namespace std;
class  complex
{
private:
    double  R;
    double  I;
public:
    complex(double real = 0, double imag = 0) //构造函数
    {
        R = real;
        I = imag;
    }
    friend ostream& operator << (ostream& out, complex& c)
    //重载运算符<<
    {
        out << "(" << c.R << ", " << c.I << ")"; //输出形式为:(实部, 虚部)
        return out;
    }
    friend istream& operator >> (istream& input, complex& c)
    //重载运算符>>
    {
        input >> c.R >> c.I;   //输入形式为:实部<空格>虚部
        return input;
    }
    complex operator + (complex& c2)                //复数加法
    {
        complex c;
        c.R = (this->R) + c2.R;
        c.I = (this->I) + c2.I;
        return c;
    }
    complex operator - (complex& c2)                //复数减法
    {
        complex c;
        c.R = (this->R) - c2.R;
        c.I = (this->I) - c2.I;
        return c;
    }
    complex operator * (complex& c2)                //复数乘法
    {
        complex c;
        double p, q, s;
        p = (this->R) * c2.R;
        q = (this->I) * c2.I;
        s = ((this->R) + (this->I)) * (c2.R + c2.I);
        c.R = p - q;
        c.I = s - p - q;
        return c;
    }
    complex operator / (complex& c2)                //复数除法
    {
        complex c;
        double p, q, s, w;
        p = (this->R) * c2.R;
        q = - (this->I) * c2.I;
        s = ((this->R) + (this->I)) * (c2.R - c2.I);
        w = (c2.R) * (c2.R) + (c2.I) * (c2.I);
        c.R = (p - q) / w;
        c.I = (s - p - q) / w;
        return c;
    }
    complex cpower(int n)                         //复数乘幂
    {
        complex  c;
        double r, q;
        q = atan2(this->I, this->R);
        r = sqrt((this->R) * (this->R) + (this->I) * (this->I));

        if (r + 1.0 != 1.0) {
            r = n * log(r);
            r = exp(r);
        }

        c.R = r * cos(n * q);
        c.I = r * sin(n * q);
        return  c;
    }
    void croot(int n)                          //复数的n次方根
    {
        complex c;
        int k;
        double r, q, t;

        if (n < 1) {
            return;
        }

        q = atan2(this->I, this->R);
        r = sqrt((this->R) * (this->R) + (this->I) * (this->I));

        if (r + 1.0 != 1.0) {
            r = (1.0 / n) * log(r);
            r = exp(r);
        }

        for (k = 0; k < n; k++) {
            t = (2.0 * k * 3.1415926 + q) / n;
            c.R = r * cos(t);
            c.I = r * sin(t);
            cout << c << endl;
        }
    }
    complex cexp()                                  //复数指数
    {
        complex c;
        double p;
        p = exp(this->R);
        c.R = p * cos(this->I);
        c.I = p * sin(this->I);
        return c;
    }
    complex clog()                                  //复数对数
    {
        complex c;
        double p;
        p = (this->R) * (this->R) + (this->I) * (this->I);
        p = log(sqrt(p));
        c.R = p;
        c.I = atan2(this->I, this->R);
        return c;
    }
    complex csin()                                  //复数正弦
    {
        complex c;
        double p, q;
        p = exp(this->I);
        q = exp(-this->I);
        c.R = sin(this->R) * (p + q) / 2;
        c.I = cos(this->R) * (p - q) / 2;
        return c;
    }
    complex ccos()                                 //复数余弦
    {
        complex c;
        double p, q;
        p = exp(this->I);
        q = exp(-this->I);
        c.R = cos(this->R) * (p + q) / 2;
        c.I = -sin(this->R) * (p - q) / 2;
        return c;
    }
};

void main()       //主函数
{
    complex  c1, c2, c;
    cout << "c1 = ";
    cin >> c1;
    cout << "c2 = ";
    cin >> c2;
    cout << c1 << " + " << c2 << " = " << c1 + c2 << endl;
    cout << c1 << " - " << c2 << " = " << c1 - c2 << endl;
    cout << c1 << " * " << c2 << " = " << c1* c2 << endl;
    cout << c1 << " / " << c2 << " = " << c1 / c2 << endl;
    cout << "c = ";
    cin >> c;
    cout << c << " 的-3次方 = " << c.cpower(-3) << endl;
    cout << c << " 的5次方根为: " << endl;
    c.croot(5);
    cout << "exp(" << c << ")  = " << c.cexp() << endl;
    cout << "log(" << c << ") = " << c.clog() << endl;
    cout << "sin(" << c << ") = " << c.csin() << endl;
    cout << "cos(" << c << ") = " << c.ccos() << endl;
}

