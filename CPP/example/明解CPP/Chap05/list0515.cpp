// 盢俱计狜经逼

#include <iostream>
using namespace std;

//--- ユ传ま计x㎝y ---//
void swap(int& x, int& y)
{
	int t = x;
	x = y;
	y = t;
}

//--- 盢ま计a, b, c狜经逼 ---//
void sort(int& a, int& b, int& c)
{
	if (a > b) swap(a, b);
	if (b > c) swap(b, c);
	if (a > b) swap(a, b);
}

int main()
{
	int a, b, c;

	cout << "跑计a";   cin >> a;
	cout << "跑计b";   cin >> b;
	cout << "跑计c";   cin >> c;

	sort(a, b, c);			// 盢a, b, c狜经逼

	cout << "盢俱计a, b, c狜经逼\n";
	cout << "跑计a琌" << a << "\n";
	cout << "跑计b琌" << b << "\n";
	cout << "跑计c琌" << c << "\n";

	return 0;
}
