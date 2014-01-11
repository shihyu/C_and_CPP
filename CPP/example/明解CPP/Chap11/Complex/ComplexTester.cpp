// 複數類別Complex的使用範例

#include <iostream>
#include "Complex.h"
using namespace std;

int main()
{
	double re, im;

	cout << "a的實的部分：";  cin >> re;
	cout << "a的虛的部分：";  cin >> im;
	Complex a(re, im);

	cout << "b的實的部分：";  cin >> re;
	cout << "b的虛的部分：";  cin >> im;
	Complex b(re, im);

	Complex c = -a + b;

	b += 2.0;			          	// 在b加上(2.0, 0.0)
	c -= Complex(1.0, 1.0);	      	// 從c減去(1.0, 1.0)
	Complex d(b.Imag(), c.Real());	// 將d作為(b的虛的部分, c的實的部分)

	cout << "a = " << a << '\n';
	cout << "b = " << b << '\n';
	cout << "c = " << c << '\n';
	cout << "d = " << d << '\n';

	return 0;
}
