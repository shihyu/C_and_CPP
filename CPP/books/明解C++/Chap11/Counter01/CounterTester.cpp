// 記數類別Counter（第１版）的使用範例

#include <iostream>
#include "Counter.h"
using namespace std;

int main()
{
	int no;
	Counter x;

	cout << "增加的次數：";  cin >> no;
	for (int i = 0; i < no; i++) {
		x.Increment();					// 增加次數
		cout << x.Value() << '\n';
	}

	cout << "減少的次數：";  cin >> no;
	for (int i = 0; i < no; i++) {
		x.Decrement();					// 減少次數
		cout << x.Value() << '\n';
	}

	return 0;
}
