// 癘计摸Counter材

#if !defined(___Class_Counter)
	#define  ___Class_Counter

#include <climits>
using namespace std;

//===== 癘计摸 =====//
class Counter {
	unsigned cnt;					// 癘计

public:
	Counter() : cnt(0) { }			// 篶

	void Increment() { if (cnt < UINT_MAX) cnt++; }		// Ω计糤
	void Decrement() { if (cnt > 0) cnt--; }		// Ω计搭ぶ
	unsigned Value() { return cnt; }			// 肚Ω计
};

#endif
