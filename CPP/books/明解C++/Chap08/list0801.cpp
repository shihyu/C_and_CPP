// 使用遞迴來求得階乘

#include <iostream>
using namespace std;

//--- 以遞迴的結構來求n的階乘 ---//
int factorial(int n)
{
	if (n > 0)
		return n * factorial(n - 1);
	else
		return 1;
}

int main()
{
	int x;

	cout << "整數值:";
	cin >> x;

	cout << x << "的階乘為" << factorial(x) << "。\n";

	return 0;
}

