// 年號版日期類別Date（實作部分)）

#include <sstream>
#include "GenDate.h"
using namespace std;

//--- 以字串傳回 ---//
string GenDate::to_string() const
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
ostream& operator<<(ostream& s, const GenDate& x)
{
	return s << x.to_string();
}
