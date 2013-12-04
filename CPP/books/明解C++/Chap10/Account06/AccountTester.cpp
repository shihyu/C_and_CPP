//  銀行帳戶類別 (第6版：使用範例)

#include <iostream>
#include "Date.h"
#include "Account.h"
using namespace std;

int main()
{
	// 足立先生的帳戶
	Account adachi("足立幸一", "12345678", 1000, Date(2005, 1, 10));
	string dw[] = {"日", "一", "二", "三", "四", "五", "六"};

	cout << "足立先生的帳戶\n";
	cout << "帳戶名＝" << adachi.GetName() << '\n';
	cout << "帳號＝" << adachi.GetNo() << '\n';
	cout << "存款餘額＝" << adachi.CheckBalance() << "元\n";
	cout << "開戶日＝" << adachi.OpeningDate();
	cout << "（" << dw[adachi.OpeningDate().DayOfWeek()] << "）\n";

	return 0;
}
