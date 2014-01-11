// 求取並顯示兩個整數值之中的較小值和較大值

#include <iostream>
using namespace std;

int main()
{
	int a, b;

	cout << "整數a：";   cin >> a;
	cout << "整數b：";   cin >> b;

	int min, max;		// 較小值 / 較大值

	if (a < b) {		// 若a比b小的話
		min = a;
		max = b;
	} else {			// 否則的話
		min = b;
		max = a;
	}

	cout << "較小值是" << min << "。\n";
	cout << "較大值是" << max << "。\n";

	return 0;
}
