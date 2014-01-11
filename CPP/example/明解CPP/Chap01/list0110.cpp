// 輸入整數值，顯示將該值的正負反轉之後的值

#include <iostream>
using namespace std;

int main()
{
	int a;					// 輸入的值

	cout << "整數值：";		// 要求輸入值
	cin >> a;					// 將輸入的整數值指定給a

	int b = -a;					// 以反轉a的正負之後的值將b初始化
	cout << "將" << a << "的正負反轉之後的值是" << b << "。\n";

	return 0;
}
