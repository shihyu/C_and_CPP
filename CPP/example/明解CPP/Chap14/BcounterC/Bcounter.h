// 偶數記數類別Bcounter

#if !defined(___Class_Bcounter)
	#define	 ___Class_Bcounter

#include "Counter.h"

class Bcounter : private Counter {

public:
	Bcounter() { }					// 建構子

	Counter::Value;					// 存取宣告

	void Increment() {				// 遞增 … 重新定義
		if (Value() < UINT_MAX - 1) {
			Counter::Increment();
			Counter::Increment();
		}
	}
};

#endif
