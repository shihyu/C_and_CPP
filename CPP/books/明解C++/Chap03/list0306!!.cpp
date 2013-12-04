// 請確認前置形式的++x是《左值運算式》
// 而後置形式的x++是《右值運算式》

#include <iostream>
using namespace std;

int main ()
{
	int x = 0;

	++x = 5;				// OK：前置形式可以置於左邊
	cout << "x的值是" << x << "\n";

	x++ = 10;				// 錯誤：後置形式不可以置於左邊
	cout << "x的值是" << x << "\n";

	return 0;
}
