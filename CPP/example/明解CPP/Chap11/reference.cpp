// 參照物件

#include <iostream>
using namespace std;

int main()
{
	double	   d = 1.0;		// d是double型態（值為1.0）
	const int& p = d;		// p參照double型態
	const int& q = 5;		// q參照常數

	const_cast<int&>(p) = 3.14;	// 3.14的指定目標是int還是double

	cout << "d = " << d << '\n';
	cout << "p = " << p << '\n';
	cout << "q = " << q << '\n';

	return 0;
}
