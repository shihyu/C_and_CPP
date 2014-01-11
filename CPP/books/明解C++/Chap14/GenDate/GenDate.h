// 年號版日期類別Date（介面部份）

#if !defined(___Class_GenDate)
	#define	 ___Class_GenDate

#include <string>
#include <iostream>
#include "Date.h"
using namespace std;

//===== 年號版日期類別 =====//
class GenDate : public Date {
public:
	enum Gengou {Meiji, Taisho, Showa, Heisei};

	GenDate() { }
	GenDate(int y, int m = 1, int d = 1) : Date(y, m, d) { }
	GenDate(Gengou g, int y, int m = 1, int d = 1) : Date(y, m, d)
	{
		switch (g) {
		 case Meiji	 : year += 1867;  break;	// 明治
		 case Taisho : year += 1911;  break;	// 大正
		 case Showa	 : year += 1925;  break;	// 昭和
		 case Heisei : year += 1988;  break;	// 平成
		}
	}
	string to_string() const;				// 以字串傳回
};

ostream& operator<<(ostream& s, const GenDate& x);		  // 插入運算子

#endif
