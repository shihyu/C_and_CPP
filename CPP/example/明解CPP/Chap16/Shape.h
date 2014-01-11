// 圖形類別Shape

#if !defined(___Class_Shape)
	#define	 ___Class_Shape

#include <iostream>
using namespace std;

//=====圖形類別（抽象類別） =====//
class Shape {
public:
	virtual void draw() = 0;		// 繪圖（純虛擬函數）
};

//===== 點 =====//
class Point : public Shape {
public:
	void draw() {
		cout << "點\n"; 
		cout << "*\n";
	}
};

//===== 水平直線 =====//
class HLine : public Shape {
	int length;			// 長度

public:
	HLine(int s) : length(s) { }

	void draw() {
		cout << "水平直線（長度：" << length << "）\n"; 
		for (int i = 1; i <= length; i++)
			cout << '*';
		cout << '\n';
	}
};

//===== 垂直直線 =====//
class VLine : public Shape {
	int length;			// 長度

public:
	VLine(int s) : length(s) { }

	void draw() {
		cout << "垂直直線（長度：" << length << "）\n"; 
		for (int i = 1; i <= length; i++)
			cout << "*\n";
	}
};

//===== 長方形 =====//
class RectAngle : public Shape {
	int width;			// 寬度
	int height;			// 高度

public:
	RectAngle(int w, int h) : width(w), height(h) { }

	void draw() {
		cout << "長方形（寬度：" << width << "　高度：" << height << "）\n"; 
		for (int i = 1; i <= height; i++) {
			for (int j = 1; j <= width; j++)
				cout << '*';
			cout << '\n';
		}
	}
};

//===== 左下為直角的等邊三角形 =====//
class Triangle : public Shape {
	int length;			// 相等之兩邊的長度

public:
	Triangle(int s) : length(s) { }

	void draw() {
		cout << "等邊三角形（長度：" << length << "）\n"; 
		for (int i = 1; i <= length; i++) {
			for (int j = 1; j <= i; j++)
				cout << '*';
			cout << '\n';
		}
	}
};

#endif
