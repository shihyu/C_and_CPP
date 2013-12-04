// 求取三個整數值的最大值 (函數版)

#include <iostream>
using namespace std;

//---傳回a, b, c的最大值---//
int max(int a, int b, int c)
{
	int max = a;
	if (b > max) max = b;
	if (c > max) max = c;
	return max;
}

int main()
{
	int a, b, c;

	cout << "整數a：";   cin >> a;
	cout << "整數b：";   cin >> b;
	cout << "整數c：";   cin >> c;

	cout << "最大值是" << max(a, b, c) << "。\n";

	return 0;
}
