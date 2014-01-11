//  銀行帳戶類別 (第5版：使用範例)

#include <iostream>
#include "Account.h"
using namespace std;

int main()
{
	Account adachi("足立幸一", "12345678", 1000, 2005, 1, 10); // 足立先生的帳戶
	Account nakata("仲田真二", "87654321",  200, 2004, 7, 15); // 仲田先生的帳戶

	adachi.Withdraw(200);	// 足立先生領了200元
	nakata.Deposit(100);	// 仲田先生存了100元

	cout << "足立先生的帳戶\n";
	cout << "帳戶名＝" << adachi.GetName() << '\n';
	cout << "帳號＝" << adachi.GetNo() << '\n';
	cout << "存款餘額＝" << adachi.CheckBalance() << "元\n";
	cout << "開戶日＝" << adachi.OpeningDate() << '\n';

	cout << "\n仲田先生的帳戶\n";
	cout << "帳戶名＝" << nakata.GetName() << '\n';
	cout << "帳號＝" << nakata.GetNo() << '\n';
	cout << "存款餘額＝" << nakata.CheckBalance() << "元\n";
	cout << "開戶日＝" << nakata.OpeningDate().Year()  << "年"
						 << nakata.OpeningDate().Month() << "月"
						 << nakata.OpeningDate().Day()   << "日\n";

	return 0;
}
