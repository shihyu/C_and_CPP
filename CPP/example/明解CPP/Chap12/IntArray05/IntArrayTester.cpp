// 整數陣列類別IntArray（第5版）的使用範例

#include <iostream>
#include "IntArray.h"
using namespace std;

int main()
{
	IntArray a(5);
	cout << "現在有" << IntArray::GetCount() << "個陣列。\n";
	{
		IntArray b(10);
		cout << "現在有" << IntArray::GetCount() << "個陣列。\n";
	}
	cout << "現在有" << IntArray::GetCount() << "個陣列。\n";

	return 0;
}
