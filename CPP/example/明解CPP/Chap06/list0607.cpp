// 求取最高的人的身高與最胖的人的體重

#include <iostream>
using namespace std;

//--- 傳回元素數n的陣列a之最大值 ---//
int maxof(const int a[], int n)
{
	int max = a[0];
	for (int i = 1; i < n; i++)
		if (a[i] > max)
			max = a[i];
	return max;
}

int main()
{
	const int ninzu = 5;				// 人數
	int height[ninzu], weight[ninzu];	// 身高、體重

	cout << "請輸入" << ninzu << "個人的身高和體重。\n";
	for (int i = 0; i < ninzu; i++) {
		cout << i + 1 << "號的身高：";
		cin >> height[i];
		cout << i + 1 << "號的體重：";
		cin >> weight[i];
	}
	int hmax = maxof(height, ninzu);	// 身高的最大值
	int wmax = maxof(weight, ninzu);	// 體重的最大值

	cout << "最高的人的身高：" << hmax << "cm\n";
	cout << "最胖的人的體重：" << wmax << "kg\n";

	return 0;
}
