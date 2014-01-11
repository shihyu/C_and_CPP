// 俱计皚摸IntArray材3ㄏノ絛ㄒ

#include <iomanip>
#include <iostream>
#include "IntArray.h"
using namespace std;

int main()
{
	int n;
	cout << "aじ计";
	cin >> n;

	IntArray a(n);				// じ计n
	for (int i = 0; i < a.Size(); i++)
		a[i] = i;

	IntArray b(1000);
	cout << "bじ计眖" << b.Size();
	b = a;						// ﹚
	cout << "跑Θ" << b.Size() << "\n";

	IntArray c = b;				// ﹍て

	cout << "    a    b    c\n";
	cout << "---------------\n";
	for (int i = 0; i < n; i++)
		cout << setw(5) << a[i] << setw(5) << b[i] << setw(5) << c[i] << '\n';

	return 0;
}
