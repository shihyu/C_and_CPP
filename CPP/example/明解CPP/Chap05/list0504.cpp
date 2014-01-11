// 求取三個整數值的最大值 (加上函數原型宣告)

#include <iostream>
using namespace std;

int max(int a, int b, int c);

int main()
{
	int a, b, c;

	cout << "變數a：";   cin >> a;
	cout << "變數b：";   cin >> b;
	cout << "變數c：";   cin >> c;

	cout << "最大值是" << max(a, b, c) << "。\n";

	return 0;
}

//--- 傳回a, b, c的最大值 ---//
int max(int a, int b, int c)
{
	int max = a;
	if (b > max) max = b;
	if (c > max) max = c;
	return max;
}
