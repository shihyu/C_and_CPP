// 整數陣列類別IntArray（第3版：介面部分）

#if !defined(___Class_IntArray)
#define ___Class_IntArray

//===== 整數陣列類別 ======//
class IntArray {
	int	size;		// 陣列的元素數
	int* vec;		                // 指向開頭元素的指標

public:
	// 明確的建構子
	explicit IntArray(int sz) : size(sz) { vec = new int[size]; }
	IntArray(const IntArray& x);					// 複製建構子
   ~IntArray() { delete[] vec; }					// 解構子
	int Size() { return size; }						// 傳回元素數
	IntArray& operator=(const IntArray& x);			// 指定運算子=
	int& operator[](int i) { return vec[i]; }		// 索引運算子[]
};

#endif
