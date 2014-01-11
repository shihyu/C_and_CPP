// 若讀入的整數值是正值的話，就判斷該值是偶數還是奇數並顯示結果

#include <iostream>
using namespace std;

int main()
{
	int n;

	cout << "整數值：";
	cin >> n;

	if (n > 0)
		if (n % 2 == 0)
			cout << "該值是偶數。\n";
		else
			cout << "該值是奇數。\n";
	else
		cout << "\a輸入的不是正值。\n";

	return 0;
}
