// 日期類別Date（第１版）的使用範例

#include <iostream>
#include "Date.h"
using namespace std;

int main()
{
	Date birthday(1963, 11, 18);		// 生日

	cout << "birthday = " << birthday.Year()  << "年"
						  << birthday.Month() << "月"
						  << birthday.Day()	  << "日\n";

	return 0;
}
