// 日期類別Date（第3版A：介面部分)

#if !defined(___Class_Date)
	#define	 ___Class_Date

#include <string>
#include <iostream>
using namespace std;

//===== 日期類別 =====//
class Date {
	int	year;		// 西元年
	int	month;		// 月
	int	day;		// 日

public:
	Date();				                	// 預設建構子
	Date(int y, int m = 1, int d = 1);		// 建構子

	int Year()	const { return this->year; }    // 傳回年
	int Month()	const { return this->month; }	// 傳回月
	int Day()	const { return this->day; }		// 傳回日
	int DayOfWeek() const;				     	// 傳回星期 
	string to_string() const;					// 以字串傳回
};

ostream& operator<<(ostream& s, const Date& x);		// 插入運算子

#endif
