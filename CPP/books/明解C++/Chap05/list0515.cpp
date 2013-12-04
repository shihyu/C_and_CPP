// 將三個整數值昇冪排序

#include <iostream>
using namespace std;

//--- 交換引數x和y的值 ---//
void swap(int& x, int& y)
{
	int t = x;
	x = y;
	y = t;
}

//--- 將引數a, b, c昇冪排序 ---//
void sort(int& a, int& b, int& c)
{
	if (a > b) swap(a, b);
	if (b > c) swap(b, c);
	if (a > b) swap(a, b);
}

int main()
{
	int a, b, c;

	cout << "變數a：";   cin >> a;
	cout << "變數b：";   cin >> b;
	cout << "變數c：";   cin >> c;

	sort(a, b, c);			// 將a, b, c昇冪排序

	cout << "將整數a, b, c昇冪排序。\n";
	cout << "變數a的值是" << a << "。\n";
	cout << "變數b的值是" << b << "。\n";
	cout << "變數c的值是" << c << "。\n";

	return 0;
}
