// 自動生命週期和靜態生命週期

#include <iostream>
using namespace std;

int fx = 0;				// 靜態生命週期＋檔案生存空間

void func()
{
	static int sx = 0;	// 靜態生命週期＋區塊生存空間
	int 	   ax = 0;	// 自動生命週期＋區塊生存空間
				
	cout << ax++ << "  " << sx++ << "  " << fx++ << '\n';
}

int main()
{
	cout << "ax sx fx\n";
	cout << "---------\n";
	for (int i = 0; i < 10; i++)
		func();

	return 0;
}
