//  銀行帳戶類別 (第4版：實作部份)

#include <string>
#include <iostream>
#include "Account.h"
using namespace std;

//--- 建構子 ---//
Account::Account(string n, string num, long z)	
{
	name = n;			// 帳戶名
	no = num;			// 帳號
	balance = z;		// 存款餘額
}

//--- 存款 ---//
void Account::Deposit(long k)
{
	balance += k;
}

//--- 提款 ---//
void Account::Withdraw(long k)
{
	balance -= k;
}
