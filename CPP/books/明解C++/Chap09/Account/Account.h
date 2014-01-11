//  銀行帳戶類別 (第4版：介面部分)

#include <string>
using namespace std;

class Account {
	string name;			// 帳戶名
	string no;				// 帳號
	long balance;			// 存款餘額

public:
	Account(string n, string num, long z);		// 建構子

	string GetName()    { return name; }		// 查詢帳戶名
	string GetNo()      { return no; }			// 查詢帳號
	long CheckBalance() { return balance; }		// 查詢存款餘額

	void Deposit(long k);						// 存款
	void Withdraw(long k);						// 提款
};
