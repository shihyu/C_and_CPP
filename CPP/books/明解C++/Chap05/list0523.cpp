// 求取兩個值的最大值、三個值的最大值之函數 (多載)

#include <iostream>
using namespace std;

//--- 傳回a, b的最大值 ---//
int max(int a, int b)
{
	return a > b ? a : b;
}

//--- 傳回a, b, c的最大值 ---//
int max(int a, int b, int c)
{
	int max = a;
	if (b > max) max = b;
	if (c > max) max = c;
	return max;
}

int main()
{
	int x, y, z;

	cout << "x的值：";
	cin >> x;

	cout << "y的值：";
	cin >> y;

	// 兩個值的最大值
	cout << "x和y的最大值是" << max(x, y) << "。\n";

	cout << "z的值：";
	cin >> z;

	// 三個值的最大值
	cout << "x、y、z的最大值是" << max(x, y, z) << "。\n";

	return 0;
}
