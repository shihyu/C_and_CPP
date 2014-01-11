// 汽車類別

#include <cmath>
#include <string>
#include <iostream>
using namespace std;

class Car {
	string name;				// 名稱
	int width, length, height; 	                                // 車寬、車長、車高
	double x, y;				// 現在位置座標
	double fuel;				// 剩餘燃料

public:
	//--- 建構子 ---//
	Car(string n, int w, int l, int h, double f) {
		name = n; width = w; length = l; height = h; fuel = f; x = y = 0.0;
	}

	double X() { return x; }			// 傳回現在位置的X座標
	double Y() { return y; }			// 傳回現在位置的Y座標
	double Fuel() { return fuel; }		                // 傳回剩餘燃料

	void PutSpec() {				// 顯示規格
		cout << "名稱：" << name << "\n"; 
		cout << "車寬：" << width << "mm\n"; 
		cout << "車長：" << length << "mm\n"; 
		cout << "車高：" << height << "mm\n"; 
	}

	bool move(double dx, double dy) {	                // 向X方向移動dx、向Y方向移動dy
		double dist = sqrt(dx * dx + dy * dy);		// 移動距離

		if (dist > fuel)
			return false;				// 燃料不足
		else {
			fuel -= dist;				// 消耗了移動距離的量的燃料
			x += dx;  y += dy;
			return true;
		}
	}
};
