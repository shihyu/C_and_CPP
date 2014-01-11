// 瞦计笴栏 (瞦0~99)

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

int main ()
{
	srand (time (NULL));		// 砞﹚睹计贺
	int no = rand () % 100;		// 璶瞦计玻ネ0°99睹计
	int x;
	cout << "瞦计笴栏秨﹍!!\n";
	cout << "叫瞦0~99计\n";

	do {
		cout << "计";
		cin >> x;
		if (x > no)
			cout << "\a琌计翅\n";
		else if (x < no)
			cout << "\a琌计翅\n";
	} while (x != no);
	cout << "タ絋氮\n";

	return 0;
}
