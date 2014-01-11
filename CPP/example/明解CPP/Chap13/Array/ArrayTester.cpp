// 陣列類別範本Array的使用範例

#include <new>
#include <iomanip>
#include <iostream>
#include "Array.h"
using namespace std;

int main()
{
	try {
		int no;
		Array<int>	  x(5);		// 元素型態為int且元素數為5
		Array<double> y(8);		// 元素型態為double且元素數為8

		cout << "資料數：";
		cin >> no;

		for (int i = 0; i < no; i++) {
			x[i] = i;
			y[i] = 0.1 * i;
			cout << "x[" << i << "] = " << x[i] << "   "
				 << "y[" << i << "] = " << y[i] << '\n';
		}
	}
	catch (bad_alloc) {
		cout << "記憶體的確保失敗了。\n";
		return 1;					         // 強制結束
	}
	catch (Array<int>::IdxRngErr x) {
		cout << "索引溢位 Array<int>：" << x.Index() << '\n';
		return 1;
	}
	catch (Array<double>::IdxRngErr x) {
		cout << "索引溢位 Array<double>：" << x.Index() << '\n';
		return 1;
	}

	return 0;
}
