// 讀入兩個整數值並顯示其中之較小值

#include <iostream>
using namespace std;

int main()
{
	int a, b;

	cout << "整數a：";   cin >> a;
	cout << "整數b：";   cin >> b;

	int min;		// 較小的值
	if (a < b)
		min = a;
	else
		min = b;

	cout << "較小的值是" << min << "。\n";

	return 0;
}
