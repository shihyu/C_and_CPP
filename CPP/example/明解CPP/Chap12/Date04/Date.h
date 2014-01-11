// 日期類別Date（第4版：介面部分)）

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
	Date();					// 預設建構子
	Date(int y, int m = 1, int d = 1);		// 建構子

	// y年是閏年嗎？
	static bool IsLeap(int y) { return y % 4 == 0 && y % 100 != 0 || y % 400 == 0; }

	int Year()  const { return year; }				// 傳回年
	int Month() const { return month; }				// 傳回月
	int Day()   const { return day; }			    // 傳回日
	bool IsLeap() const { return IsLeap(year); }		                                // 是閏年嗎
	int DayOfWeek() const;						    // 傳回星期
	string to_string() const;						// 以字串傳回
};

ostream& operator<<(ostream& s, const Date& x);		// 插入運算子

#endif
