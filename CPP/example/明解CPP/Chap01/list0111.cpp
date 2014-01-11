// 輸入兩個實數值之後，顯示將其加減乘除後的值

#include <iostream>
using namespace std;

int main()
{
	double x;			// 用來加減乘除的值
	double y;			// 用來加減乘除的值

	cout <<"將x與y做加減乘除的計算。\n";

	cout << "x的值：";			// 要求輸入x的值
	cin >> x;						// 將輸入的實數值指定給x

	cout << "y的值：";			// 要求輸入y的值
	cin >> y;						// 將輸入的實數值指定給y 

	cout << "x + y是" << x + y << "。\n";	// 顯示x + y的值
	cout << "x - y是" << x - y << "。\n ";	// 顯示x - y的值
	cout << "x * y是" << x * y << "。\n ";	// 顯示x * y的值
	cout << "x / y是" << x / y << "。\n ";	// 顯示x / y的值

	return 0;
}
