// 日期類別Date（加上成員函數呼叫次數的計算）

#include <iostream>
using namespace std;

class Date {
	int	year;			// 西元年
	int	month;			// 月
	int	day;			// 日
	mutable int count;	// 成員函數被呼叫出來的總計次數

public:
	Date(int y, int m, int d) {				// 建構子
		year = y; month = m; day = d; count = 0;
	}
	int Year()  const { count++; return year; }			// 傳回年
	int Month() const { count++; return month; }		// 傳回月
	int Day()	const { count++; return day; }			// 傳回日
	int Count()	const { return count; }			// 記數
};

int main()
{
	const Date birthday(1963, 11, 18);		// 生日

	cout << "birthday = " << birthday.Year()  << "年"
						  << birthday.Month() << "月"
						  << birthday.Day()	  << "日\n";
	cout << "birthday的成員函數一共被呼叫了" << birthday.Count() << 
			"次。\n";

	return 0;
}
