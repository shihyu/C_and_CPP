//  銀行帳戶類別 (第2版)

#include <string>
#include <iostream>
using namespace std;

class Account {
private:
	string name;			// 帳戶名
	string no;				// 帳號
	long balance;			// 存款餘額

public:
	Account(string n, string num, long z) {		// 建構子
		name = n;			// 帳戶名
		no = num;			// 帳號
		balance = z;		// 存款餘額
	}

	string GetName() {			// 查詢帳戶名
		return name;
	}

	string GetNo() {			// 查詢帳號
		return no;
	}

	long CheckBalance() {		// 查詢存款餘額
		return balance;
	}

	void Deposit(long k) {		// 存款
		balance += k;
	}

	void Withdraw(long k) {		// 提款
		balance -= k;
	}
};

int main()
{
	Account adachi("足立幸一", "12345678", 1000);		// 足立先生的帳戶
	Account nakata("仲田真二", "87654321",  200);		// 仲田先生的帳戶

	adachi.Withdraw(200);			// 足立先生領了200元
	nakata.Deposit(100);			// 仲田先生存了100元

	cout << "■足立先生的帳戶：\"" << adachi.GetName() << "\" ("
		 << adachi.GetNo() << ") " << adachi.CheckBalance() << "元\n";

	cout << "■仲田先生的帳戶：\"" << nakata.GetName() << "\" ("
		 << nakata.GetNo() << ") " << nakata.CheckBalance() << "元\n";

	return 0;
}
