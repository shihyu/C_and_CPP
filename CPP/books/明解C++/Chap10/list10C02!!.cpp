// 定義的範例之一：會因為處理系統不同而有所差別

struct tm {
	int tm_sec;	// 秒（0～61）
	int tm_min;	// 分（0～59）
	int tm_hour; 	// 點（0～23）
	int tm_mday; 	// 日（1～31）
	int tm_mon;	// 從1月開始的月數（0～11）
	int tm_year; 	// 從1900年開始的年數
	int tm_wday; 	// 星期：星期日～星期六（0～6）
	int tm_yday; 	// 從1月1日開始的日數（0～365）
	int tm_isdst;	// 夏季時間差
};
