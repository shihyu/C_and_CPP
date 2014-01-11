// 日期類別Date（第2版：介面部分）

#include <string>
#include <iostream>
using namespace std;

class Date {
	int	year;		// 西元年
	int	month;		// 月
	int	day;		// 日

public:
	Date();					// 預設建構子
	Date(int y, int m = 1, int d = 1);		// 建構子

	int Year()  const { return year; }		// 傳回年
	int Month() const { return month; }		// 傳回月
	int Day()   const { return day; }		// 傳回日
	string to_string() const;			// 以字串傳回
};

ostream& operator<<(ostream& s, const Date& x);		// 插入子
