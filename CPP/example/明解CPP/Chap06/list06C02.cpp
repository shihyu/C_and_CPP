// 指標 ->整數的型態轉換

#include <iostream>
using namespace std;

int main()
{
	int n;
	cout << "n的位址：" << hex << reinterpret_cast<unsigned long>(&n) << '\n';
	return 0;
}
