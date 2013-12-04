// 使用日期類別Date（第１版）來進行初始化與指定

#include <iostream>
#include "Date.h"
using namespace std;

Date::Date(int y, int m, int d) 
: year(y)
, month(m)
, day(d) {
}

int main()
{
	Date x(2010, 11, 25);  // 初始化
	Date y = x;							// 初始化
	Date z = Date(2052, 10, 12);		// 初始化

	z = x;								// 指定
	y = Date(2107, 3, 6);				// 指定

	cout << "X = "
		 << x.Year() << "年" << x.Month() << "月" << x.Day() << "日\n";

	cout << "y = "
		 << y.Year() << "年" << y.Month() << "月" << y.Day() << "日\n";

	cout << "z = "
		 << z.Year() << "年" << z.Month() << "月" << z.Day() << "日\n";

	return 0;
}
