// ―俱计程 (ㄧ计)

#include <iostream>
using namespace std;

//---肚a, b, c程---//
int max(int a, int b, int c)
{
	int max = a;
	if (b > max) max = b;
	if (c > max) max = c;
	return max;
}

int main()
{
	int a, b, c;

	cout << "俱计a";   cin >> a;
	cout << "俱计b";   cin >> b;
	cout << "俱计c";   cin >> c;

	cout << "程琌" << max(a, b, c) << "\n";

	return 0;
}
