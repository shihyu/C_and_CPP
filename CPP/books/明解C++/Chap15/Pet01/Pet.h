// 寵物類別Pet（第１版：介面部分）

#if !defined(___Class_Pet)
	#define	 ___Class_Pet

#include <string>
#include <iostream>
using namespace std;

//===== 寵物類別 =====//
class Pet {
public:
	enum PetType {Dog, Cat, Monkey};	// 寵物的種類

private:
	PetType kind;		// 種類
	string  name;		// 名字

public:
	// 建構子
	Pet(PetType x = Dog, string n = "") : kind(x), name(n) { }

	PetType Type() const { return kind; }		// 傳回種類
	string Name()  const { return name; }		// 傳回名字

	void Input();				// 讀入
	void Sintro() const;		// 自我介紹
};

// 插入運算子
ostream& operator<<(ostream&, const Pet&);

#endif
