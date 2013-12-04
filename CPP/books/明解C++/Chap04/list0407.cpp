// 顯示各種整數型態和變數的大小

#include <iostream>
using namespace std;
 
int main()
{
	char c;
	cout << "char型態的大小：" << sizeof(char) << '\n';
	cout << "變數c的大小：" << sizeof(c)    << '\n';

	short h;
	cout << "short型態的大小：" << sizeof(short) << '\n';
	cout << "變數h的大小  ：" << sizeof(h)     << '\n';

	int i;
	cout << "int型態的大小 ：" << sizeof(int) << '\n';
	cout << "變數i的大小  ：" << sizeof(i)   << '\n';

	long l;
	cout << "long型態的大小 ：" << sizeof(long) << '\n';
	cout << "變數l的大小  ：" << sizeof(l)    << '\n';

	return 0;
}
