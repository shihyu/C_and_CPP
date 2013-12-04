// 顯示現在的日期、時間

#include <ctime>
#include <iostream>
using namespace std;

int main()
{
	time_t current = time(NULL);				// 現在的標準時間
	struct tm *timer = localtime(&current);		// 各元素的時間（地方時間）
	char *wday_name[] = {"日", "一", "二", "三", "四", "五", "六"};

	cout << "現在的日期、時間為"
		 << timer->tm_year + 1900     << "年"
		 << timer->tm_mon + 1         << "月"
		 << timer->tm_mday            << "日（"
		 << wday_name[timer->tm_wday] << "）"
		 << timer->tm_hour            << "點"
		 << timer->tm_min             << "分"
		 << timer->tm_sec             << "秒。\n";

	return 0;
}
