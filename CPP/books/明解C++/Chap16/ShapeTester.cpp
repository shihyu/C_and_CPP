// 圖形類別Shape的使用範例

#include <iostream>
#include "Shape.h"
using namespace std;

int main()
{ 
	Shape* v[5];

	v[0] = new Point();				// 點
	v[1] = new HLine(4);			// 水平直線
	v[2] = new VLine(2);			// 垂直直線
	v[3] = new RectAngle(4, 3);		// 長方形
	v[4] = new Triangle(5);			// 等邊三角形

	for (int i = 0; i < 5; i++)
		v[i]->draw();		                // 畫出所有圖形

	return 0;
}
