// 記數類別Counter (第2版)

#if !defined(___Class_Counter)
	#define  ___Class_Counter

#include <climits>
using namespace std;

//===== 記數類別 =====//
class Counter {
	unsigned cnt;					// 記數

public:
	Counter() : cnt(0) { }				// 建構子

	operator unsigned() { return cnt; }		// 轉換函數 unsigned(op)

	bool operator!() { return cnt == 0; }	// 邏輯否定運算子 !op

	Counter& operator++() {				// 前置遞增運算子 ++op
		if (cnt < UINT_MAX) cnt++;
		return *this;
	}

	Counter operator++(int) {			// 後置遞增運算子 op++
		Counter x = *this;
		if (cnt < UINT_MAX) cnt++;
		return x;
	}

	Counter& operator--() {				// 前置遞減運算子 --op
		if (cnt > 0) cnt--;
		return *this;
	}

	Counter operator--(int) {			// 後置遞減運算子 op--
		Counter x = *this;
		if (cnt > 0) cnt--;
		return x;
	}
};

#endif
