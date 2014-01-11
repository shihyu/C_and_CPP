// 顯示左下側為直角的直角三角形 (函數版)

#include <iostream>
using namespace std;

//--- 連續顯示n個'*'字元 ---//
void put_stars(int n)
{
	while (n-- > 0)
		cout << '*';
}

int main()
{
	int n;

	cout << "顯示左下側為直角的直角三角形。\n";
	cout << "層數：";
	cin >> n;

	for (int i = 1; i <= n; i++) {
		put_stars(i);
		cout << '\n';
	}

	return 0;
}
