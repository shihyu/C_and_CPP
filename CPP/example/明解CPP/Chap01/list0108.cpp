// 輸入兩個整數值，並顯示將它們加減乘除之後的值

#include <iostream>
using namespace std;

int main()
{
	int x;			// 用來加減乘除的值
	int y;			// 用來加減乘除的值

	cout << "將x與y做加減乘除的計算。\n";

	cout << "x的值：";		// 要求輸入x的值
	cin >> x;				// 將整數值指定給x

	cout << "y的值：";		// 要求輸入y的值
	cin >> y;				// 將整數值指定給y 

	cout << "x + y是" << x + y << "。\n";		// 顯示x + y的值
	cout << "x - y是" << x - y << "。\n ";		// 顯示x - y的值
	cout << "x * y是" << x * y << "。\n ";		// 顯示x * y的值
	cout << "x / y是" << x / y << "。\n ";		// 顯示x / y的值 (商)
	cout << "x % y是" << x % y << "。\n ";	// 顯示x % y的值 (餘數)

	return 0;
}
