// 顯示輸入之月份的季節

#include <iostream>
using namespace std;

int main()
{
	int month;

	cout << "求得季節。\n哪個月份：";
	cin >> month;

	if (month >= 3 && month <= 5)					// 3月、4月、5月
		cout << "那是春季。\n";
	else if (month >= 6 && month <= 8)				// 6月、7月、8月
		cout << "那是夏季。\n";
	else if (month >= 9 && month <= 11)				// 9月、10月、11月
		cout << "那是秋季。\n";
	else if (month == 12 || month == 1 || month == 2)		// 12月、1月、2月
		cout << "那是冬季。\n";

	return 0;
}
