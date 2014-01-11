// 布林值類別Boolean的使用範例

#include <iostream>
#include "Boolean.h"
using namespace std;

//---整數x與y是否相等 ---//
Boolean int_eq(int x, int y)
{
	return x == y;
}

int main()
{
	Boolean a;				// a ← False
	Boolean b = 100;		// b ← True：Boolean(100)
	int     c;
	Boolean x[8];			// x[0]～x[7] ← False

	cout << "整數值：";
	cin >> c;
	x[0] = int_eq(c, 5);	// x[0]
	x[1] = (c != 3);		// x[1] ← Boolean(c != 3)
	x[2] = Boolean::False;	// x[2] ← False
	x[3] = 1000;			// x[3] ← True：Boolean(1000)

	cout << "a的值：" << int(a) << '\n';
	cout << "b的值：" << (const char*)b << '\n';

	for (int i = 0; i < 8; i++)
		cout << "x[" << i << "] = " << x[i] << '\n';

	return 0;
}
