// 自動生命週期和靜態生命週期

#include <iostream>
using namespace std;

int fx;					// 靜態生命週期 (以0來初始化)

int main()
{
	static int sx;		// 靜態生命週期 (以0來初始化)
	int 	   ax;		// 自動生命週期 (以不定值來初始化)

	cout << "ax = " << ax << '\n';
	cout << "sx = " << sx << '\n';
	cout << "fx = " << fx << '\n';

	return 0;
}
