// 動態產生、初始化整數物件

#include <iostream>
using namespace std;

int main()
{
	int* x = new int(5);				// 產生：附加初始化子

	cout << "*x = " << *x << '\n';

	delete x;						// 丟棄

	return 0;
}
