// 年號版日期類別Date的使用範例

#include <iostream>
#include "Date.h"
using namespace std;

int main()
{
	int y, m, d;
	cout << "請輸入生日。\n";
	cout << "年：";	  cin >> y;
	cout << "月：";	  cin >> m;
	cout << "日：";	  cin >> d;
	Date birthday(y, m, d);
	cout << "該日為" << birthday << '\n';
	cout << "該年" 
		 << (birthday.IsLeap() ? "是閏年。\n" : "不是閏年。\n"); 

	Date today;						// 今天的日期
	cout << "今天是" << today.Year()  << "年"
					 << today.Month() << "月"
					 << today.Day()	  << "日。\n";
	Date meiji( Date::Meiji,  1,  9,  8);	// 明治的第一天
	Date taisho(Date::Taisho, 1,  7, 30);	// 大正的第一天
	Date showa( Date::Showa,  1, 12, 25);	// 昭和的第一天
	Date heisei(Date::Heisei, 1,  1,  8);	// 平成的第一天

	cout << "以字串表示明治的第一天：\"" << meiji.to_string()  << "\"\n";
	cout << "以字串表示大正的第一天：\"" << taisho.to_string() << "\"\n";
	cout << "以字串表示昭和的第一天：\"" << showa.to_string()  << "\"\n";
	cout << "以字串表示平成的第一天：\"" << heisei.to_string() << "\"\n";

	return 0;
}
