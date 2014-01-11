// 日期類別Date（第3版：實作部分)

#include <ctime>
#include <sstream>
#include <iostream>
#include "Date.h"
using namespace std;

//--- Date的預設建構子（今天的日期）---//
Date::Date()
{
	time_t current = time(NULL);			// 取得現在的標準時間
	struct tm* local = localtime(&current);		// 轉換為各元素的時間
	year  = local->tm_year + 1900;		// 年：tm_year是年-1900
	month = local->tm_mon + 1;			// 月：tm_mon是0∼11
	day	  = local->tm_mday;
}

//--- Date的建構子（指定好的年月日）---//
Date::Date(int y, int m, int d)
{
	year  = y;
	month = m;
	day	  = d;
}

//--- 以字串傳回 ---//
string Date::to_string() const
{
	ostringstream s;
	s << year << "年" << month << "月" << day << "日";
	return s.str();
}

//--- 傳回星期（星期日∼星期六分別對應0∼6）---//
int Date::DayOfWeek() const
{
	int y = year;
	int m = month;
	if (m == 1 || m == 2) {
		y--;
		m += 12;
	}
	return (y + y / 4 - y / 100 + y / 400 + (13 * m + 8) / 5 + day) % 7;
}

//--- 在輸出串流s中插入x ---//
ostream& operator<<(ostream& s, const Date& x)
{
	return s << x.to_string();
}
