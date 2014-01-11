// 癘计摸Counter材ㄏノ絛ㄒ

#include <iostream>
#include "Counter.h"
using namespace std;

int main()
{
	int no;
	Counter x;

	cout << "糤Ω计";  cin >> no;
	for (int i = 0; i < no; i++) {
		x.Increment();					// 糤Ω计
		cout << x.Value() << '\n';
	}

	cout << "搭ぶΩ计";  cin >> no;
	for (int i = 0; i < no; i++) {
		x.Decrement();					// 搭ぶΩ计
		cout << x.Value() << '\n';
	}

	return 0;
}
