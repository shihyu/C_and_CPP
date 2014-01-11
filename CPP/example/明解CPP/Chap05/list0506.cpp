// 求取次方

#include <iostream>
using namespace std;

//--- 傳回x的n次方 ---//
double power(double x, int n)
{
	double tmp = 1.0;

	while (n-- > 0)
		tmp *= x;	//將x提交到tmp 
	return tmp;
}

int main()
{
	double a;
	int    b;

	cout << "求取a的b次方。\n";
	cout << "實數a：";	cin >> a;
	cout << "整數b：";	cin >> b;
	cout << a << "的" << b << "次方是" << power(a, b) << "。\n";

	return 0;
}
