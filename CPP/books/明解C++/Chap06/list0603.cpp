// 位址運算子和間接參照運算子

#include <iostream>
using namespace std;

int main()
{
	int x = 100;
	int y = 200;
	cout << "x = " << x << '\n';
	cout << "y = " << y << '\n';
	cout << "-------\n";

	int* ptr = &x;				// ptr指向x
	*ptr = 300;				// 將300指定給*ptr (也就是x)
	cout << "x = " << x << '\n';
	cout << "y = " << y << '\n';
	cout << "-------\n";

	ptr = &y;					// ptr指向y
	*ptr = 400;				// 將400指定給*ptr (也就是y)
	cout << "x = " << x << '\n';
	cout << "y = " << y << '\n';

	return 0;
}
