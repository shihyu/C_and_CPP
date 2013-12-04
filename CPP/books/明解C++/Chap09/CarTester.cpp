// 汽車類別的使用範例

#include <iostream>
#include "Car.h"
using namespace std;

int main()
{
	string name;
	int width, length, height;
	double gas;
	cout << "請輸入車子的資料。\n";
	cout << "名稱是：";  cin >> name;
	cout << "車寬是：";  cin >> width;
	cout << "車長是：";  cin >> length;
	cout << "車高是：";  cin >> height;
	cout << "汽油的量是：";  cin >> gas;

	Car myCar(name, width, length, height, gas);
	myCar.PutSpec();		// 顯示規格

	while (true) {
		cout << "目前位置(" << myCar.X() << ", " << myCar.Y() << ")\n";
		cout << "剩餘燃料：" << myCar.Fuel() << '\n';
		cout << "是否移動[0…No／1…Yes]：";
		int move;
		cin >> move;
		if (move == 0) break;

		double dx, dy;
		cout << "往Ｘ方向的移動距離：";  cin >> dx;
		cout << "往Ｙ方向的移動距離：";  cin >> dy;
		if (!myCar.move(dx, dy))
			cout << "\a燃料不足！\n";
	}
}
