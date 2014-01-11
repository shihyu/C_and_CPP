//  確認識別字的生存空間

#include <iostream>
using namespace std;

int x = 700;

void print_x()
{
	cout << "x = " << x << '\n';
}

int main()
{
	cout << "x = " << x << '\n';

	int x = 800;

	cout << "x = " << x << '\n';

	for (int i = 0; i < 5; i++) {
		int x = i * 100;
		cout << "x = " << x << '\n';
	}

	cout << "x = " << x << '\n';
	cout << "::x = " << ::x << '\n';
	print_x();

	return 0;
}
