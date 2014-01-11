// 陣列類別範本Array

#if !defined(___Class_Array)
	#define  ___Class_Array

//===== 陣列類別範本 =====//
template <class Type> class Array {
	int	size;		// 陣列的元素數
	Type* vec;		// 指向開頭元素的指標

public:
	//----- 索引範圍錯誤 -----//
	class IdxRngErr {
		Array* ident;
		int index;
	public:
		IdxRngErr(Array* p, int i) : ident(p), index(i) { }
		int Index() { return index; }
	};

	// 明確的建構子
	explicit Array(int sz) : size(sz) { vec = new Type[size]; }

	// 複製建構子
	Array(const Array& x) {
		vec = new Type[x.size];	    // 將元素數設為與x相同的值
		size = x.size;				// 確保陣列主體
		for (int i = 0; i < size; i++)		 // 複製x的所有元素
			vec[i] = x.vec[i];
	}

	// 解構子
   ~Array() { delete[] vec; }

	// 傳回元素數
	int Size() { return size; }

	// 指定運算子=
	Array& operator=(const Array& x) {
		if (&x != this) {			// 如果不是指定自己本身的話…
			delete[] vec;			// 解放原本確保的記憶體區域
			size = x.size;			// 新的元素數
			vec = new Type[size];		// 確保新的記憶體區域
			for (int i = 0; i < size; i++)	// 複製所有元素
				vec[i] = x.vec[i];
		}
		return *this;
	}

	// 索引運算子[]
	Type& operator[](int i)	{
		if (i < 0 || i >= size)
			throw IdxRngErr(this, i);		// 送出索引範圍錯誤
		return vec[i];
	}
};

#endif
