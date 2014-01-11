// 寵物類別Pet（第2版：介面部分）

#if !defined(___Class_Pet)
	#define	 ___Class_Pet

#include <string>
#include <iostream>
using namespace std;

//=== 寵物類別Pet ===//
class Pet {
	string name;						// 名字

public:
	Pet(string n = "") : name(n) { }					// 建構子

	string Name() const { return name; }				// 傳回名字

	void Input() { 						// 讀入
		cout << "名字 : ";	cin >> name;
	}

	void Sintro() const {						// 自我介紹
		cout << "我的名字是" << name << "。\n";
	}
};

ostream& operator<<(ostream&, const Pet&);				// 插入運算子

//=== 狗寵物類別Pdog ===//
class Pdog : public Pet {
	string dtype;							// 品種

public:
	Pdog(string n = "", string d = "") : Pet(n), dtype(d) { }

	string Type() const { return dtype; }				// 傳回種類	

	void Input() {						// 讀入
		Pet::Input();
		cout << "品種 : "; cin >> dtype;
	}

	void Sintro() const {						// 自我介紹
		cout << "我是" << dtype << Name() << "!!\n";
	}
};

ostream& operator<<(ostream&, const Pdog&);				// 插入運算子

//=== 貓寵物類別Pcat ===//
class Pcat : public Pet {
public:
	Pcat(string n = "") : Pet(n) { }

	// 不定義成員函數Input

	void Sintro() const {						// 自我介紹
		cout << "我的名字是" << Name() << "!!\n";
	}
};

ostream& operator<<(ostream&, const Pcat&);				// 插入運算子

//=== 猴寵物類別Pmonkey ===//
class Pmonkey : public Pet {
	int age;							// 年齡
public:
	Pmonkey(string n = "", int a = 0) : Pet(n), age(a) { }

	int Age() const { return age; }					// 傳回年齡	

	void Input() {						// 讀入
		Pet::Input();
		cout << "年齡 : "; cin >> age;
	}

	void Sintro() const {						// 自我介紹
		cout << "我是" << age << "歲的" << Name() << "!!\n";
	}
};

ostream& operator<<(ostream&, const Pmonkey&);			// 插入運算子

#endif
