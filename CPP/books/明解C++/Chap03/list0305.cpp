// 從正整數值倒數至0為止 (第2版)

#include <iostream>
using namespace std;

int main ()
{
	int x;

	cout << "開始倒數。\n";
	do {
		cout << "正整數值：";
		cin >> x;
	} while (x <= 0);

	while (x >= 0)
		cout << x-- << "\n";	// 顯示x的值並遞減

	return 0;
}
