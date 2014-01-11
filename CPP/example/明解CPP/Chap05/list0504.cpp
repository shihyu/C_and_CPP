// ―俱计程 (ㄧ计)

#include <iostream>
using namespace std;

int max(int a, int b, int c);

int main()
{
	int a, b, c;

	cout << "跑计a";   cin >> a;
	cout << "跑计b";   cin >> b;
	cout << "跑计c";   cin >> c;

	cout << "程琌" << max(a, b, c) << "\n";

	return 0;
}

//--- 肚a, b, c程 ---//
int max(int a, int b, int c)
{
	int max = a;
	if (b > max) max = b;
	if (c > max) max = c;
	return max;
}
