//  銀行帳戶類別 (第6版：介面部分)

#if !defined(___Class_Account)
	#define	 ___Class_Account

#include <string>
#include "Date.h"
using namespace std;

//===== 銀行帳戶類別 =====//
class Account {
	string name;			// 帳戶名
	string no;				// 帳號
	long balance;			// 存款金額
	Date open;			// 開戶日

public:
	// 建構子
	Account(string n, string num, long z, Date op);

	void Deposit(long k);						// 存款
	void Withdraw(long k);						// 提款
	string GetName() const    { return name; }		// 查詢帳戶名
	string GetNo() const      { return no; }		                // 查詢帳號
	long CheckBalance()	const { return balance; }	// 查詢存款餘額
	Date OpeningDate() const  { return open; }		// 查詢開戶日
};

#endif
