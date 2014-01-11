// 年號版日期類別GenDate的使用範例

#include <iostream>
#include "Date.h"
#include "GenDate.h"
using namespace std;

int main()
{
	int y, m, d;
	cout << "請輸入生日。\n";
	cout << "年：";	  cin >> y;
	cout << "月：";	  cin >> m;
	cout << "日：";	  cin >> d;
	GenDate birthday(y, m, d);
	cout << "年號：" << birthday.to_string()       << '\n';
	cout << "西元：" << birthday.Date::to_string() << '\n';
	cout << "該年" 
		 << (birthday.IsLeap() ? "是閏年。\n" : "不是閏年。\n"); 

	GenDate today;						// 今天的日期
	cout << "今天是" << today.Year()  << "年"
					 << today.Month() << "月"
					 << today.Day()	  << "日。\n";
	GenDate meiji( GenDate::Meiji,  1,  9,  8);		// 明治的第一天
	GenDate taisho(GenDate::Taisho, 1,  7, 30);		// 大正的第一天
	GenDate showa( GenDate::Showa,  1, 12, 25);		// 昭和的第一天
	GenDate heisei(GenDate::Heisei, 1,  1,  8);		// 平成的第一天

	cout << "以字串傳回明治的第一天：\"" << meiji.to_string()  << "\"\n";
	cout << "以字串傳回大正的第一天：\"" << taisho.to_string() << "\"\n";
	cout << "以字串傳回昭和的第一天：\"" << showa.to_string()  << "\"\n";
	cout << "以字串傳回平成的第一天：\"" << heisei.to_string() << "\"\n";

	return 0;
}
