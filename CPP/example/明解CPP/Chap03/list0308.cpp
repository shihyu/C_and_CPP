// 讀入正整數值後以相反的順序顯示

#include <iostream>
using namespace std;

int main ()
{
	int x;

	cout << "以相反的順序顯示正整數值。\n";
	do {
		cout << "正整數值：";
		cin >> x;
	} while (x <= 0);

	cout << "反過來讀則是";
	while (x > 0) {
		cout << x % 10;			// 顯示x的最小位數
		x /= 10;					// 將x除以10
	}
    cout << "。\n";

	return 0;
}
