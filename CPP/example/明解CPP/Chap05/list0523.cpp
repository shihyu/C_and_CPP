// ―ㄢ程程ぇㄧ计 (更)

#include <iostream>
using namespace std;

//--- 肚a, b程 ---//
int max(int a, int b)
{
	return a > b ? a : b;
}

//--- 肚a, b, c程 ---//
int max(int a, int b, int c)
{
	int max = a;
	if (b > max) max = b;
	if (c > max) max = c;
	return max;
}

int main()
{
	int x, y, z;

	cout << "x";
	cin >> x;

	cout << "y";
	cin >> y;

	// ㄢ程
	cout << "x㎝y程琌" << max(x, y) << "\n";

	cout << "z";
	cin >> z;

	// 程
	cout << "xyz程琌" << max(x, y, z) << "\n";

	return 0;
}
