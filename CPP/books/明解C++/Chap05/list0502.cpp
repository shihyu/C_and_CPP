// 求取三個人的身高、體重和年齡之最大值並顯示 (函數版)

#include <iostream>
using namespace std;

//--- 傳回a, b, c的最大值 ---//
int max(int a, int b, int c)
{
	int max = a;
	if (b > max) max = b;
	if (c > max) max = c;
	return max;
}

int main()
{
	int height[3];	              	// 身高
	int weight[3];					// 體重
	int age[3];				    	// 年齡

	for (int i = 0; i < 3; i++) {		// 讀入
		cout << "[" << i + 1 << "] ";
		cout << "身高：";	cin >> height[i];
		cout << "體重：";	cin >> weight[i];
		cout << "年齡：";	cin >> age[i];
	}
    	
	int max_height = max(height[0], height[1], height[2]);	//身高之最大值
	int max_weight = max(weight[0], weight[1], weight[2]);	//體重之最大值
	int max_age = max(age[0], age[1], age[2]);				//年齡之最大值

	cout << "身高之最大值是" << max_height << "。\n";
	cout << "體重之最大值是" << max_weight << "。\n";
	cout << "年齡之最大值是" << max_age << "。\n";

	return 0;
}
