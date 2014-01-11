// 輸入兩個整數值之後，顯示將其加減乘除後的值

#include <iostream>
using namespace std;

int main()
{
	int x;			// 用來加減乘除的值
	int y;			// 用來加減乘除的值

	cout << "將x與y做加減乘除的計算。\n ";

	cout << "x的值和y的值：";		// 要求輸入x的值和y的值
	cin >> x >> y;						// 將輸入的整數值指定給x和y 

	cout << "x + y是" << x + y << "。\n";	// 顯示x + y的值
	cout << "x - y是" << x - y << "。\n "; 	// 顯示x - y的值
	cout << "x * y是" << x * y << "。\n ";	// 顯示x * y的值
	cout << "x / y是" << x / y << "。\n "; 	// 顯示x / y的值 (商)
	cout << "x % y是" << x % y << "。\n ";	// 顯示x % y的值 (餘數)

	return 0;
}
