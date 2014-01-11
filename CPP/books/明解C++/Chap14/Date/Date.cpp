// 年號版日期類別Date（實作部份）

#include <ctime>
#include <sstream>
#include <iostream>
#include "Date.h"
using namespace std;

//--- 預設建構子 ---//
Date::Date()
{
	time_t current = time(NULL);			// 取得現在的時間
	struct tm* local = localtime(&current);	// 轉換為各元素的時間
	year  = local->tm_year + 1900;			// 年：tm_year是年-1900
	month = local->tm_mon + 1;				// 月：tm_mon是0～11
	day	  = local->tm_mday;
}

//--- 傳回星期（星期日～星期六分別對應0～6）---//
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

//--- 以字串傳回 ---//
string Date::to_string() const
{
	unsigned long idate = year * 10000UL + month * 100UL + day;
	ostringstream s;

	if (idate < 18680908UL)
		s << year;
	else if (idate < 19120730UL)
		s << "明治" << (year - 1867);
	else if (idate < 19261225UL)
		s << "大正" << (year - 1911);
	else if (idate < 19890108UL)
		s << "昭和" << (year - 1925);
	else
		s << "平成" << (year - 1988);
	s << "年" << month << "月" << day << "日";

	return s.str();
}

//--- 插入到ostream ---//
ostream& operator<<(ostream& s, const Date& x)
{
	return s << x.to_string();
}
