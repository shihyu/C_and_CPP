// 盢ㄢま计ユ传ㄧ计

#include <iostream>
using namespace std;

//--- ユ传ま计x㎝y ---//
void swap(int& x, int& y)
{
	int t = x;
	x = y;
	y = t;
}

int main()
{
	int a, b;

	cout << "跑计a";   cin >> a;
	cout << "跑计b";   cin >> b;

	swap(a, b);							// ユ传a㎝b

	cout << "ユ传跑计a㎝b\n";
	cout << "跑计a琌" << a << "\n";
	cout << "跑计b琌" << b << "\n";

	return 0;
}
