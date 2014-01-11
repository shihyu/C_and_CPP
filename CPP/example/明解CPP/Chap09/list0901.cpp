// 銀行帳戶

#include <string>
#include <iostream>
using namespace std;

int main()
{
	string adachi_account_name = "足立幸一";	// 足立先生的帳戶名
	string adachi_account_no = "12345678";		// 　〃　的帳號
	long  adachi_account_balance = 1000;		// 　〃　的存款餘額

	string nakata_account_name = "仲田真二";	// 仲田先生的帳戶名
	string nakata_account_no = "87654321";		// 　〃　的帳號
	long  nakata_account_balance = 200;			// 　〃　的存款餘額

	adachi_account_balance -= 200;				// 足立先生領了200元
	nakata_account_balance += 100;				// 仲田先生存了100元

	cout << "■足立先生的帳戶：\"" << adachi_account_name << "\" ("
		 << adachi_account_no << ") " << adachi_account_balance << "元\n";

	cout << "■仲田先生的帳戶：\"" << nakata_account_name << "\" ("
		 << nakata_account_no << ") " << nakata_account_balance << "元\n";

	return 0;
}
