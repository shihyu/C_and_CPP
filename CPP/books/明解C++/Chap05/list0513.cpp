// 參照物件

#include <iostream>
using namespace std;

int main()
{
	int  x = 1;
	int  y = 2;
	int& a = x;					// 以x來將a初始化 (a參照x)
	cout << "a = " << a << '\n';
	cout << "x = " << x << '\n';
	cout << "y = " << y << '\n';

	a = 5;						// 將5指定給a
	cout << "a = " << a << '\n';
	cout << "x = " << x << '\n';
	cout << "y = " << y << '\n';

	return 0;
}
