// 堆疊 類別範本

#if !defined(___Class_Stack)
	#define  ___Class_Stack

//===== 堆疊 類別範本 =====//
template<class Type> class Stack {
	int size;			// 堆疊的容量
	int	ptr;			// 堆疊指標
	Type* stk;			// 堆疊的主體（指向開頭元素的指標）

	Stack(const Stack&);			// 讓複製建構子無效
	Stack& operator=(const Stack&);	// 讓指定運算子無效

public:
	// 明確的建構子
	explicit Stack(int sz) : size(sz), ptr(0) { stk = new Type[size]; }
   ~Stack() { delete[] stk; }						// 解構子

	//----- 對於已滿堆疊的推入之例外 -----//
	class OverflowErr {
		Stack* ident;
	public:
		OverflowErr(Stack* p) : ident(p) { }
		Stack* vec() { return ident; }
	};

	Type& Push(const Type& x) {				// 推入
		if (ptr >= size)					// 堆疊已滿
			throw OverflowErr(this);
		return stk[ptr++] = x;
	}

	//----- 對於來自空堆疊的彈出之例外 -----//
	class EmptyErr {
		Stack* ident;
	public:
		EmptyErr(Stack* p) : ident(p) { }
		Stack* vec() { return ident; }
	};
		
	Type& Pop() {                       // 彈出
		if (ptr <= 0)					// 堆疊是空的
			throw EmptyErr(this);
		return stk[--ptr];
	}
};

#endif
