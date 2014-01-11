// 抽象堆疊類別

#if !defined(___Class_Stack)
#define ___Class_Stack

#include <vector>
#include <cstdlib>
using namespace std;

//===== 抽象堆疊類別 =====//
template <class Type> class Stack {
public:
	class EmptyErr { };				          // 例外：堆疊為空的

	virtual ~Stack() { }				      // 虛擬解構子
	virtual void Push(const Type) = 0;		  // 推入
	virtual Type Pop() = 0;				      // 彈出
};

//===== 向量版堆疊類別 =====//
template <class Type> class VecStack : public Stack<Type> {
	vector<Type> stk;				          // 向量

	VecStack(const VecStack&);			      // 讓複製建構子無效化
	VecStack& operator=(const VecStack&);	  // 讓指定運算子無效化

public:
	VecStack() { }					// 建構子

	~VecStack() { }					// 解構子

	void Push(const Type x) {			// 推入
		stk.push_back(x);				// 插入到尾端
	}

	Type Pop() {						// 彈出
		if (stk.size() <= 0)
			throw EmptyErr();			// 堆疊為空的
		Type x = stk.back();			// 調查尾端的值
		stk.pop_back();					// 刪除尾端元素
		return x;
	}
};

//===== 線形清單版堆疊類別 =====//
template <class Type> class ListStack : public Stack<Type> {

	template <class Type> class Node {
		friend class ListStack<Type>;
		Type* data;		// 資料
		Node* next;		// 後續指標 (指向後續節點的指標)
	public:
		Node(Type* d, Node* n) : data(d), next(n) { }
	};

	Node<Type>* top;				// 指向前端節點的指標
	Node<Type>* dummy;				// 指向假節點的指標

	ListStack(const ListStack&);			// 讓複製建構子無效化
	ListStack& operator=(const ListStack&); // 讓指定運算子無效化

public:
	ListStack() {						// 建構子
		top = dummy = new Node<Type>(NULL, NULL);
	}

	~ListStack() {						// 解構子
		Node<Type>* ptr = top;
		while (ptr != dummy) {
			Node<Type>* next = ptr->next;
			delete ptr->data;
			delete ptr;
			ptr = next;
		}
		delete dummy;
	}

	void Push(const Type x) {		     // 推入
		Node<Type>* ptr = top;
		top = new Node<Type>(new Type(x), ptr);
	}

	Type Pop() {						// 彈出
		if (top == dummy)
			throw EmptyErr();			// 堆疊為空的
		else {
			Node<Type>* ptr = top->next;
			Type temp = *(top->data);
			delete top->data;
			delete top;
			top = ptr;
			return temp;
		}
	}
};

#endif
