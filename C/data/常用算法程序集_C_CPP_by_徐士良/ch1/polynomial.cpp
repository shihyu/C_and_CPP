//POLYNOMIAL.CPP
//实多项式计算
#include  <iostream>
#include  <iomanip>
#include  <fstream>
#include  <cmath>
using namespace std;
class  polynomial
{
private:
    int n;         //多项式次数
    double*  p;
public:
    polynomial(int nn)
    {
        n = nn;
        p = new double[n + 1]; //动态分配内存
    }
    void  file_input();   //由文件读入多项式系数
    void  input();        //由键盘输入多项式系数
    void  output();       //输出多项式系数到文件并显示
    double poly_value(double);  //多项式求值
    void poly_mul(polynomial&, polynomial&); //多项式相乘
    void poly_div(polynomial&, polynomial&, polynomial&);
    //多项式相除
    ~polynomial()
    {
        delete [] p;
    }
};

void polynomial::file_input()  //由文件读入多项式系数
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

    for (i = 0; i < n + 1; i++) {
        fin >> p[i];    //读入多项式系数
    }

    fin.close();
}

void polynomial::input()  //由键盘输入多项式系数
{
    int  i;
    cout << "多项式系数:" << endl;

    for (i = 0; i < n + 1; i++) {      //输入多项式系数
        cout << "p(" << i << ") = ";
        cin >> p[i];
    }
}

void polynomial::output()  //输出多项式系数到文件并显示
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
        fout << p[i] << endl;
    }

    fout.close();
}

double polynomial::poly_value(double x)           //多项式求值p(x)
{
    int k;
    double u;
    u = p[n];

    for (k = n - 1; k >= 0; k--) {
        u = u * x + p[k];
    }

    return u;
}

void polynomial::poly_mul(polynomial& p2, polynomial& p3)
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

void polynomial::poly_div(polynomial& p2, polynomial& p3, polynomial& p4)
//多项式相除 p3 = p/p2 + p4
{
    int i, j, mm, ll;

    for (i = 0; i <= p3.n; i++) {
        p3.p[i] = 0.0;
    }

    if (p2.p[p2.n] + 1.0 == 1.0) {
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
    int k;
    double x[6] = { 0.9, 1.1, 1.3, -0.9, -1.1, -1.3};
    polynomial  p(6), p2(5), q2(3), s2(8), p3(4), q3(2), s3(2), r3(1);
    p.file_input();        //由文件读入多项式p系数
    cout << "多项式求值: " << endl;

    for (k = 0; k < 6; k++) {
        cout << "p(" << x[k] << ") = " << p.poly_value(x[k]) << endl;
    }

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

