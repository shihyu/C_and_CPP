// 整數陣列類別IntArray（第5版：實作部分）

#include "IntArray.h"

int IntArray::counter = 0;

//--- 增加次數 ---//
void IntArray::CountUp()
{
	counter++;
}

//--- 減少次數 ---//
void IntArray::CountDown()
{
	counter--;
}

//--- 傳回次數 ---//
int IntArray::GetCount()
{
	return counter;
}

//--- 複製建構子 ---//
IntArray::IntArray(const IntArray& x)
{
	size = x.size;				// 將元素數設為與x相同的值
	vec = new int[size];				// 確保陣列主體
	for (int i = 0; i < size; i++)		// 複製所有元素
		vec[i] = x.vec[i];
	CountUp();
}

//--- 指定運算子 ---//
IntArray& IntArray::operator=(const IntArray& x)
{
	if (&x != this) {				// 如果不是指定自己本身的話…
		delete[] vec;				// 解放原本確保的記憶體區域
		size = x.size;				// 新的元素數
		vec = new int[size];			// 確保新的記憶體區域
		for (int i = 0; i < size; i++)	// 複製所有元素
			vec[i] = x.vec[i];
	}
	return *this;
}
