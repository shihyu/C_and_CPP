// 用操作子指定格式

#include <iomanip>
#include <iostream>
using namespace std;

int main ()
{
	cout << oct << 1234 << '\n';		// 8進位
	cout << dec << 1234 << '\n';		// 10進位
	cout << hex << 1234 << '\n';		// 16進位

	cout << showbase;
	cout << oct << 1234 << '\n';		// 8進位
	cout << dec << 1234 << '\n';		// 10進位
	cout << hex << 1234 << '\n';		// 16進位

	cout << setw (10) << internal << "abc\n";
	cout << setw (10) << left	 << "abc\n";
	cout << setw (10) << right	 << "abc\n";

	cout << setbase (10);
	cout << setw (10) << internal << -123 << endl;
	cout << setw (10) << left	 << -123 << endl;
	cout << setw (10) << right	 << -123 << endl;

	cout << setfill ('*');
	cout << setw (10) << internal << -123 << endl;
	cout << setw (10) << left	 << -123 << endl;
	cout << setw (10) << right	 << -123 << endl;
	cout << setfill (' ');

	cout << fixed    << setw (10) << setprecision (2) << 123.5 << endl;
	cout << scientific << setw (10) << setprecision (2) << 123.5 << endl;

	return 0;
}
