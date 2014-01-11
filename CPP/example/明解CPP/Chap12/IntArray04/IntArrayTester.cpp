// 整數陣列類別IntArray（第4版）的使用範例

#include <new>
#include <iomanip>
#include <iostream>
#include "IntArray.h"
using namespace std;

//--- 將num個資料指定給元素數為size的陣列並顯示 --//
void f(int size, int num)
{
	try {
		IntArray x(size);
		for (int i = 0; i < num; i++) {
			x[i] = i;
			cout << "x[" << i << "] = " << x[i] << '\n';
		}
	}
	catch (IntArray::IdxRngErr& x) {
		cout << "索引溢位：" << x.Index() << '\n';
		return;
	}
	catch (bad_alloc) {
		cout << "確保記憶體失敗。\n";
		exit(1);			               // 強制結束
	}
}

int main()
{
	int size, num;

	cout << "元素數："; cin >> size;
	cout << "資料數："; cin >> num;

	f(size, num);

	return 0;
}
