// 顯示double型態的特性

#include <limits>
#include <iostream>
using namespace std;

int main()
{
	cout << "最小值：" << numeric_limits<double>::min() << '\n';
	cout << "最大值：" << numeric_limits<double>::max() << '\n';
	cout << "假數部份：" << numeric_limits<double>::radix  << "進位數是"
					   << numeric_limits<double>::digits << "位數\n";
	cout << "位數：" << numeric_limits<double>::digits10 << '\n';
	cout << "機械ε：" << numeric_limits<double>::epsilon()<< '\n';
	cout << "最大的捨去誤差" << numeric_limits<double>::round_error() << '\n';
	cout << "捨去形式：";
		switch (numeric_limits<double>::round_style) {
		 case round_indeterminate:
							cout << "無法決定。\n"; break;
		 case round_toward_zero:
							cout << "趨近於0捨去。\n"; break;
		 case round_to_nearest:
							cout << "以可表現的最接近值捨去。\n"; break;
		 case round_toward_infinity:
							cout << "趨近於無限大捨去。\n"; break;
		 case round_toward_neg_infinity:
							cout << "趨近於負的無限大捨去。\n"; break;
		}

	return 0;
}
