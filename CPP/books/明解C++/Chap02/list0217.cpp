// 調查是否為閏年

#include <iostream>
using namespace std;

int main()
{
	int y;

	cout << "輸入年：";
	cin >> y;

	cout << "該年";
	if (y % 4 == 0 and y % 100 != 0
				   or  y % 400 == 0)
		cout << "是閏年。\n";
	else
		cout << "不是閏年。\n";

	return 0;
}
