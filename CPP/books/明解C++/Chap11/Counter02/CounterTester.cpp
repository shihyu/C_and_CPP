// 記數類別Counter (第2版)的使用範例

#include <iostream>
#include "Counter.h"
using namespace std;

int main()
{
	int no;
	Counter x;
	Counter y;

	cout << "增加的次數：";  cin >> no;
	for (int i = 0; i < no; i++)
		cout << x++ << ' ' << ++y << '\n';	// 增加次數

	cout << "減少的次數：";  cin >> no;
	for (int i = 0; i < no; i++)
		cout << x-- << ' ' << --y << '\n'; 	// 減少次數

	if (!x)
		cout << "x是0。\n";
	else 
		cout << "x不是0。\n";

	return 0;
}
