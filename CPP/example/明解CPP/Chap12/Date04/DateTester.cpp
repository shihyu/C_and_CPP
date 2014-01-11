// 日期類別Date（第4版)的使用範例

#include <iostream>
#include "Date.h"
using namespace std;

int main()
{
	int y, m, d;
	cout << "西元年：";
	cin >> y;
	cout << "該年"
		 << (Date::IsLeap(y) ? "是閏年。\n" : "不是閏年。\n"); 

	cout << "請輸入生日。\n";
	cout << "年：";	  cin >> y;
	cout << "月：";	  cin >> m;
	cout << "日：";	  cin >> d;
	Date birthday(y, m, d);
	cout << birthday.Year() << "年" 
		 << (birthday.IsLeap() ? "是閏年。\n" : "不是閏年。\n"); 

	return 0;
}
