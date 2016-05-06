//COM_POLY.CPP
//复系数多项式计算
#include  <iostream.h>
#include  <iomanip.h>
#include  <fstream.h>
#include  <math.h>
#include  <stdlib.h>
//  using namespace std;
class  complex           //基类complex类
{
protected:
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
    double cfabs(complex& c)                     //复数模
    {
        double s;
        s = (c.R) * (c.R) + (c.I) * (c.I);
        s = sqrt(s);
        return s;
    }
};

class  com_poly: public complex //声明com_poly是基类complex类的派生类
{
private:
    int n;              //多项式次数
    complex*  p;        //复系数多项式
public:
    com_poly(int nn)
    {
        n = nn;
        p = new complex[n + 1]; //动态分配内存
    }
    void  file_input();   //由文件读入多项式系数
    void  input();        //由键盘输入多项式系数
    void  output();       //输出多项式系数到文件并显示
    complex poly_value(complex);  //多项式求值
    void poly_mul(com_poly&, com_poly&); //多项式相乘
    void poly_div(com_poly&, com_poly&, com_poly&);
    //多项式相除
    ~com_poly()
    {
        delete [] p;
    }
};

void com_poly::file_input()  //由文件读入多项式系数
{
    int  i;
    char str1[20];
    cout << "\n输入文件名:  ";
    cin >> str1;
    ifstream  fin(str1);

    if (!fin) {
        cout << "\n不能打开这个文件 " << str1 << endl;
        exit(1);
    }

    for (i = 0; i < n + 1; i++) { //读入多项式系数
        fin >> p[i];
    }

    fin.close();
}

void com_poly::input()  //由键盘输入多项式系数
{
    int  i;
    cout << "多项式系数:" << endl;

    for (i = 0; i < n + 1; i++) {      //输入多项式系数
        cout << "p(" << i << ") = ";
        cin >> p[i];
    }
}

void com_poly::output()  //输出多项式系数到文件并显示
{
    int i;
    char str2[20];
    cout << "\n输出文件名:  ";
    cin >> str2;
    ofstream fout(str2);

    if (!fout) {
        cout << "\n不能打开这个文件 " << str2 << endl;
        exit(1);
    }

    for (i = 0; i < n + 1; i++) {
        cout << "p(" << i << ")=" << p[i] << endl;
    }

    for (i = 0; i < n + 1; i++) {
        fout << p[i] << endl;
    }

    fout.close();
}

complex com_poly::poly_value(complex x)   //多项式求值p(x)
{
    int k;
    complex u;
    u = p[n];

    for (k = n - 1; k >= 0; k--) {
        u = u * x + p[k];
    }

    return u;
}

void com_poly::poly_mul(com_poly& p2, com_poly& p3)
//多项式相乘 p3 = p*p2
{
    int i, j;

    for (i = 0; i <= p3.n; i++) {
        p3.p[i] = 0.0;
    }

    for (i = 0; i <= n; i++)
        for (j = 0; j <= p2.n; j++) {
            p3.p[i + j] = p3.p[i + j] + (this->p[i]) * p2.p[j];
        }

    return ;
}

void com_poly::poly_div(com_poly& p2, com_poly& p3, com_poly& p4)
//多项式相除 p3 = p/p2 + p4
{
    int i, j, mm, ll;

    for (i = 0; i <= p3.n; i++) {
        p3.p[i] = 0.0;
    }

    if (cfabs(p2.p[p2.n]) + 1.0 == 1.0) {
        return;
    }

    ll = n;

    for (i = (p3.n) + 1; i >= 1; i--) {
        p3.p[i - 1] = p[ll] / (p2.p[p2.n]);
        mm = ll;

        for (j = 1; j <= p2.n; j++) {
            p[mm - 1] = p[mm - 1] - p3.p[i - 1] * (p2.p[(p2.n) - j]);
            mm = mm - 1;
        }

        ll = ll - 1;
    }

    for (i = 0; i <= p4.n; i++) {
        p4.p[i] = p[i];
    }

    return;
}

void main()       //主函数
{
    com_poly  p(3), p2(5), q2(3), s2(8), p3(4), q3(2), s3(2), r3(1);
    complex x;
    cout << "输入x = ";
    cin >> x;
    p.input();             //从键盘输入多项式p系数
    cout << "多项式求值: " << endl;
    cout << "p(" << x << ") = " << p.poly_value(x) << endl;
    p2.file_input();         //由文件读入多项式p2系数
    q2.file_input();         //由文件读入多项式q2系数
    p2.poly_mul(q2, s2);     //多项式相乘 s2 = p2*q2
    cout << "乘积多项式s2:" << endl;
    s2.output();             //输出乘积多项式s2的系数到文件并显示
    p3.file_input();        //由文件读入多项式p3系数
    q3.file_input();        //由文件读入多项式q3系数
    p3.poly_div(q3, s3, r3);   //多项式相除 s3 = p3/q3 + r3
    cout << "商多项式s3:" << endl;
    s3.output();               //输出商多项式s3的系数到文件并显示
    cout << "余多项式r3:" << endl;
    r3.output();               //输出余多项式r3的系数到文件并显示
}

