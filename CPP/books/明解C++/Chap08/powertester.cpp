// 傳回次方運算之值的函數

#include <iostream>
using namespace std;

//--- 傳回x的n次方 ---//
double power(double x, int n);

int main()
{
	double a;
	int    b;

	cout << "求a的b次方。\n";
	cout << "實數a：";	cin >> a;
	cout << "整數b：";	cin >> b;
	cout << a << "的" << b << "次方為" <<
			power(a, b) << "。\n";

	return 0;
}

