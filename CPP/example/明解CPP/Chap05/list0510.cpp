// 顯示右下側為直角的直角三角形 (函數版)

#include <iostream>
using namespace std;

//--- 連續顯示n個字元c ---//
void put_nchar(char c, int n)
{
	while (n-- > 0)
		cout << c;
}

int main()
{
	int n;

	cout << "顯示右下側為直角的直角三角形。\n";
	cout << "層數：";
	cin >> n;

	for (int i = 1; i <= n; i++) {
		put_nchar(' ', n - i);		// 顯示n – i個' '
		put_nchar('+', i);			// 顯示i個'+'
		cout << '\n';
	}

	return 0;
}
