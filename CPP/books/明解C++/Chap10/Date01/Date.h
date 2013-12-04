// 日期類別Date（第１版：介面部分）

class Date {
	int	year;		// 西元年
	int	month;		// 月
	int	day;		// 日

public:
	Date(int y, int m, int d);				// 建構子
	int Year()	{ return year; }			// 傳回年
	int Month() { return month; }			// 傳回月
	int Day()	{ return day; }				// 傳回日
};
