// 日期類別Date（第3版)的使用範例 … 書中未刊登之程式

#include <string>
#include <iostream>
#include "Date.h"
using namespace std;

int main()
{
	Date today;						// 今天的日期
	Date birthday(1963, 11, 18);		                                                // 生日
	Date day[3];						// 陣列（今天的日期）
	string dw[] = {"日", "一", "二", "三", "四", "五", "六"};

	cout << "today    = " << today;
	cout << "（" << dw[today.DayOfWeek()] << "）\n";

	cout << "today的字串表現：\"" << today.to_string() << "\"\n"; 

	cout << "birthday = " << birthday;
	cout << "（" << dw[birthday.DayOfWeek()] << "）\n";
	for (int i = 0; i < 3; i++) {
		cout << "day[" << i << "] = " << day[i];
		cout << "（" << dw[day[i].DayOfWeek()] << "）\n";
	}

	return 0;
}

