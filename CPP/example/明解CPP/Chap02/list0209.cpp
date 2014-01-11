// 讀入兩個整數值並顯示其中之較小值

#include <iostream>
using namespace std;

int main()
{
	int a, b;

	cout << "整數a：";   cin >> a;
	cout << "整數b：";   cin >> b;

	int min = a < b ? a : b;		//較小的值

	cout << "較小的值是" << min << "。\n";

	return 0;
}
