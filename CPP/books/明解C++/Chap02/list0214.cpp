// 讀入的實數值可以被10整除嗎？

#include <cmath>
#include <iostream>
using namespace std;

int main()
{
	double x;

	cout << "實數值：";
	cin >> x;

	if (double m = fmod(x, 10)) {
		cout << "該值不能被10整除。\n";
		cout << "餘數是" << m << "。\n";
	} else {
		cout << "該值可以被10整除。\n";
	}

	return 0;
}
