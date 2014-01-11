//  銀行帳戶類別 (第4版)的使用範例

#include <string>
#include <iostream>
#include "Account.h"
using namespace std;

int main()
{
	Account* adachi = new Account("足立幸一", "12345678", 1000);
	Account* nakata = new Account("仲田真二", "87654321",  200);

	adachi->Withdraw(200);		// 足立先生領了200元
	nakata->Deposit(100);		// 仲田先生存了100元

	cout << "■足立先生的帳戶：\"" << adachi->GetName() << "\" ("
		 << adachi->GetNo() << ") " << adachi->CheckBalance() << "元\n";

	cout << "■仲田先生的帳戶：\"" << nakata->GetName() << "\" ("
		 << nakata->GetNo() << ") " << nakata->CheckBalance() << "元\n";

	return 0;
}
