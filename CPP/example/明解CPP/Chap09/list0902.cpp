//  銀行帳戶類別 (第1版)

#include <string>
#include <iostream>
using namespace std;

class Account {
public:
	string name;			// 帳戶名
	string no;				// 帳號
	long balance;			// 存款餘額
};

int main()
{
	Account adachi;				// 足立先生的帳戶
	Account nakata;				// 仲田先生的帳戶

	adachi.name = "足立幸一";	// 足立先生的帳戶名
	adachi.no = "12345678";		// 　〃　的帳號
	adachi.balance = 1000;		// 　〃　的存款餘額

	nakata.name = "仲田真二";	// 仲田先生的帳戶名
	nakata.no = "87654321";		// 　〃　的帳號
	nakata.balance = 200;		// 　〃　的存款餘額

	adachi.balance -= 200;		// 足立先生領了200元
	nakata.balance += 100;		// 仲田先生存了100元

	cout << "■足立先生的帳戶：\"" << adachi.name << "\" ("
		 << adachi.no << ") " << adachi.balance << "元\n";

	cout << "■仲田先生的帳戶：\"" << nakata.name << "\" ("
		 << nakata.no << ") " << nakata.balance << "元\n";

	return 0;
}
