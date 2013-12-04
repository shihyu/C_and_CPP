// 交換兩個引數的值的函數 (錯誤)

#include <iostream>
using namespace std;

//--- 交換引數x和y的值 (錯誤) ---//
void swap(int x, int y)
{
	int t = x;
	x = y;
	y = t;
}

int main()
{
	int a, b;

	cout << "變數a：";   cin >> a;
	cout << "變數b：";   cin >> b;

	swap(a, b);			// 交換a和b?

	cout << "交換變數a和b的值。\n";
	cout << "變數a的值是" << a << "。\n";
	cout << "變數b的值是" << b << "。\n";

	return 0;
}
