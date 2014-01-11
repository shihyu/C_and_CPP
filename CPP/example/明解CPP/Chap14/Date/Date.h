// 年號版日期類別Date（介面部份）

#if !defined(___Class_Date)
	#define	 ___Class_Date

#include <string>
#include <iostream>
using namespace std;

//===== 年號版日期類別Date =====//
class Date {
public:
	enum Gengou {Meiji, Taisho, Showa, Heisei};		// 年號
private:
	int year;			// 西元年
	int month;			// 月
	int day;			// 日
public:
	Date();						// 預設建構子
	Date(int y, int m = 1, int d = 1) :			// 建構子（西元）
			year(y), month(m), day(d) { }
	Date(Gengou g, int y, int m = 1, int d = 1) {	// 建構子（年號）
		switch (g) {
		 case Meiji	 : y += 1867;  break;	// 明治
		 case Taisho : y += 1911;  break;	// 大正
		 case Showa	 : y += 1925;  break;	// 昭和
		 case Heisei : y += 1988;  break;	// 平成
		}
		year = y;  month = m;  day = d;
	}
	// y年是閏年嗎？
	static bool IsLeap(int y) { return y % 4 == 0 && y % 100 != 0 || y % 400 == 0; }
	int Year()	const { return year; }		// 傳回年
	int Month() const { return month; }		// 傳回月
	int Day()	const { return day; }		// 傳回日
	int DayOfWeek() const;					// 傳回星期 
	bool IsLeap() const { return IsLeap(year); }		// 是閏年嗎？
	string to_string() const;				// 以字串傳回
};

ostream& operator<<(ostream& s, const Date& x);		// 插入子

#endif
