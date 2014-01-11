// 記數類別Counter（第１版）

#if !defined(___Class_Counter)
	#define  ___Class_Counter

#include <climits>
using namespace std;

//===== 記數類別 =====//
class Counter {
	unsigned cnt;					// 記數

public:
	Counter() : cnt(0) { }			// 建構子

	void Increment() { if (cnt < UINT_MAX) cnt++; }		// 次數增加
	void Decrement() { if (cnt > 0) cnt--; }		// 次數減少
	unsigned Value() { return cnt; }			// 傳回次數
};

#endif
