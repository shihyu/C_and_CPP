// 交叉轉型

#include <iostream>
#include "ShapeWindow.h"
using namespace std;

int main()
{
	Shape* s = new HLine(5);				// 水平直線

	if (Window* w = dynamic_cast<Window*>(s))		// 不是視窗
		cout << "面積為" << w->area() << "。\n";	// 無法求得面積


	Shape* r = new RectAngle(3, 5);				// 長方形

	if (Window* w = dynamic_cast<Window*>(r))		// 因為是視窗
		cout << "面積為" << w->area() << "。\n";	               								// 可求得面積


	Window* t = new Triangle(4);				// 等邊三角形

	if (Shape* s = dynamic_cast<Shape*>(t))			// 因為是圖形
		s->draw();															// 可以繪圖

	delete s;
	delete r;
	delete t;

	return 0;
}
