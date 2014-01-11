// 癘计摸Counter (材2)ㄏノ絛ㄒ

#include <iostream>
#include "Counter.h"
using namespace std;

int main()
{
	int no;
	Counter x;
	Counter y;

	cout << "糤Ω计";  cin >> no;
	for (int i = 0; i < no; i++)
		cout << x++ << ' ' << ++y << '\n';	// 糤Ω计

	cout << "搭ぶΩ计";  cin >> no;
	for (int i = 0; i < no; i++)
		cout << x-- << ' ' << --y << '\n'; 	// 搭ぶΩ计

	if (!x)
		cout << "x琌0\n";
	else 
		cout << "xぃ琌0\n";

	return 0;
}
