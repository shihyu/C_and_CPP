//  銀行帳戶類別 (第6版：實作部分)

#include <string>
#include <iostream>
#include "Account.h"
using namespace std;

//--- 建構子 ---//
Account::Account(string n, string num, long z, Date op) : 
		name(n), no(num), balance(z), open(op)
{
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
