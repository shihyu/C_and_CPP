// 求取三個整數值中的最大值

#include <iostream>
using namespace std;

int main()
{
	int a, b, c;

	cout << "整數a：";   cin >> a;
	cout << "整數b：";   cin >> b;
	cout << "整數c：";   cin >> c;

	int max = a;
	if (b > max) max = b;
	if (c > max) max = c;

	cout << "最大值是" << max << "。\n";

	return 0;
}
