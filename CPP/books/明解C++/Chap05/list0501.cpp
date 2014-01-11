// 求取三個人的身高、體重和年齡之最大值並顯示

#include <iostream>
using namespace std;

int main()
{
	int height[3];					// 身高
	int weight[3];					// 體重
	int age[3];					// 年齡

	for (int i = 0; i < 3; i++) {		// 讀入
		cout << "[" << i + 1 << "] ";
		cout << "身高：";	cin >> height[i];
		cout << "體重：";	cin >> weight[i];
		cout << "年齡：";	cin >> age[i];
	}

	int max_height = height[0];						// 身高之最大值

	if (height[1] > max_height) max_height = height[1];
	if (height[2] > max_height) max_height = height[2];

	int max_weight = weight[0];						// 體重之最大值

	if (weight[1] > max_weight) max_weight = weight[1];
	if (weight[2] > max_weight) max_weight = weight[2];

	int max_age = age[0];							// 年齡之最大值

	if (age[1] > max_age) max_age = age[1];
	if (age[2] > max_age) max_age = age[2];

	cout << "身高之最大值是" << max_height << "。\n";
	cout << "體重之最大值是" << max_weight << "。\n";
	cout << "年齡之最大值是" << max_age << "。\n";

	return 0;
}
