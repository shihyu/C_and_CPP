// 指標的基本 (位址運算子和間接參照運算子)

#include <iostream>
using namespace std;

int main()
{
	int x = 135;
	cout << "x   ：" <<  x << '\n';
	cout << "&x  ：" << &x << "位址\n";

	int* ptr = &x;		// ptr指向x
	cout << "ptr ：" <<	 ptr << "位址\n";
	cout << "*ptr：" << *ptr << '\n';

	return 0;
}
