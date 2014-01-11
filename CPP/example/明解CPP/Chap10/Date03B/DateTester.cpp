// 使用指向成員函數的指標來動態呼叫函數

#include <iostream>
#include "Date.h"
using namespace std;

int main()
{
	typedef int (Date::*pcomp)(int) const;
	pcomp fcomp[] = {&Date::CompY, &Date::CompM, &Date::CompD};
	int	  menu;
	const Date birthday(1963, 11, 18);

	cout << "請猜猜看我的生日。\n";
	do {
		cout << "0…年/1…月/2…日/3…結束：";
		cin >> menu;

		if (menu >= 0 && menu <= 2) {
			int value;
			cout << "是多少呢：";
			cin >> value;

			int diff = (birthday.*fcomp[menu])(value);
			if (!diff)
				cout << "正確答案。\n";
			else if (diff > 0)
				cout << "多了" <<  diff << "。\n";
			else
				cout << "少了" << -diff << "。\n";
		}
	  } while (menu != 3);

	return 0;
}
