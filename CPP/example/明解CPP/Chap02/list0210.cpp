// ―俱计い程

#include <iostream>
using namespace std;

int main()
{
	int a, b, c;

	cout << "俱计a";   cin >> a;
	cout << "俱计b";   cin >> b;
	cout << "俱计c";   cin >> c;

	int max = a;
	if (b > max) max = b;
	if (c > max) max = c;

	cout << "程琌" << max << "\n";

	return 0;
}
