// 將二列三行的矩陣相加

#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
	int a[2][3] = { {1, 2, 3}, {4, 5, 6} };
	int b[2][3] = { {6, 3, 4}, {5, 1, 2} };
	int c[2][3] = { {0, 0, 0}, {0, 0, 0} };

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			c[i][j] = a[i][j] + b[i][j];

	cout << "矩陣a\n";					// 顯示矩陣a的元素的值
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++)
			cout << setw(3) << a[i][j];
		cout << '\n';
	}

	cout << "矩陣b\n";					// 顯示矩陣b的元素的值
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++)
			cout << setw(3) << b[i][j];
		cout << '\n';
	}

	cout << "矩陣c\n";					// 顯示矩陣c的元素的值
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++)
			cout << setw(3) << c[i][j];
		cout << '\n';
	}

	return 0;
}
