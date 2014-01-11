// 使用#if指令來達成的程式加註

#include <iostream>
using namespace std;

#define	DEBUG	0

int main()
{
	int	a = 5;
	int	x = 1;

#if DEBUG == 1
	a = x;				/*將x指定給a */
#endif

	cout << "a的值為" << a << "。\n";

	return 0;
}
