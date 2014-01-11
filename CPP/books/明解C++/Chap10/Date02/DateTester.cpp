// 日期類別Date（第2版）的使用範例

#include <iostream>
#include "Date.h"
using namespace std;

int main()
{
	Date today;							// 今天的日期
	Date birthday(1963, 11, 18);		// 生日
	Date day[3];						// 陣列（今天的日期）

	cout << "today   = " << today << '\n';
	cout << "today的字串顯示：\"" << today.to_string() << "\"\n"; 
	cout << "birthday = " << birthday << '\n';
	for (int i = 0; i < 3; i++)
		cout << "day[" << i << "] = " << day[i] << '\n';

	return 0;
}
