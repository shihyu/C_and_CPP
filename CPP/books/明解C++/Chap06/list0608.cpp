// 動態產生整數物件

#include <iostream>
using namespace std;

int main()
{
	int* x = new int;			// 產生 (確保記憶區域)

	cout << "整數：";
	cin >> *x;

	cout << "*x = " << *x << '\n';

	delete x;					// 丟棄 (釋放記憶區域)

	return 0;
}
