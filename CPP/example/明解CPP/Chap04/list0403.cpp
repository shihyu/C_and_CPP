// 判斷單純字元型態是有符號還是無符號

#include <climits>
#include <iostream>
using namespace std;

int main()
{
	cout << "此處理器的單純字元型態是"
		 <<	(CHAR_MIN ? "有符號" : "無符號")
		 <<	"字元型態。\n";

	return 0;
}
