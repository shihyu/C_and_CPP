// ら戳摸DateΘㄧ计㊣Ω计璸衡

#include <iostream>
using namespace std;

class Date {
	int	year;			// ﹁じ
	int	month;			// る
	int	day;			// ら
	mutable int count;	// Θㄧ计砆㊣ㄓ羆璸Ω计

public:
	Date(int y, int m, int d) {				// 篶
		year = y; month = m; day = d; count = 0;
	}
	int Year()  const { count++; return year; }			// 肚
	int Month() const { count++; return month; }		// 肚る
	int Day()	const { count++; return day; }			// 肚ら
	int Count()	const { return count; }			// 癘计
};

int main()
{
	const Date birthday(1963, 11, 18);		// ネら

	cout << "birthday = " << birthday.Year()  << ""
						  << birthday.Month() << "る"
						  << birthday.Day()	  << "ら\n";
	cout << "birthdayΘㄧ计砆㊣" << birthday.Count() << 
			"Ω\n";

	return 0;
}
