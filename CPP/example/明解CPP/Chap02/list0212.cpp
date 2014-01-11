// 將兩個變數昇冪排序 (由小到大)

#include <iostream>
using namespace std;

int main()
{
	int a, b;

	cout << "變數a：";   cin >> a;
	cout << "變數b：";   cin >> b;

	if (a > b) {		// 若a比b大的話
		int t = a;		// 將兩個值交換
		a = b;
		b = t;
	}
	cout << "以讓a ≦ b來排序。\n";
	cout << "變數a是" << a << "。\n";
	cout << "變數b是" << b << "。\n";

	return 0;
}
