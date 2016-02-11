#include <iostream>
#include <iomanip>
#include <string>
#include <functional>           // 提供 : less  greater
#include <algorithm>            // 提供 : sort

using  namespace  std ;

// 定義 姓名 年齡  性別 資料型別
typedef  string    NAME ;
typedef  unsigned  AGE  ;
enum     GENDER    { female , male } ;

// 學生類別
class  Student {

  private :
    
    NAME    name   ;  // 姓名
    AGE     age    ;  // 年齡
    GENDER  gender ;  // 性別
    
  public :

    Student( NAME n , AGE a ,GENDER g ) 
        : name(n) , age(a) , gender(g) {}
    
    AGE     get_age()    const {  return age ;    }

    friend  ostream& operator << ( ostream& out , 
                                   const Student& foo ) ;

};

// 輸出學生資料
ostream& operator << ( ostream& out , const Student& foo ) {
    return  out << "姓名 : " << setw(6) << foo.name.c_str() 
                << " [" << ( foo.gender == female ? 'F' : 'M' ) 
                << "]"  << setw(5) << " 年齡 : " << foo.age  ;
}

// 函式類別 : 比較年齡 (比較的樣板型別參數內定為 less<AGE>)
template <class  Compare = less<AGE> >
struct  by_age {
    bool operator() ( const Student* a , const Student* b ) const {
        return  Compare()( a->get_age() , b->get_age() ) ;
    }
};

int  main() {

    int i ;
    const  int  Student_No = 5 ;
    
    // 學生陣列
    Student  foo[Student_No] = { 
        Student("John" ,13,male) , Student("Mary" ,10,female) ,
        Student("Tony" ,17,male) , Student("Amy"  ,10,female) ,
        Student("Grace",18,female) } ;

    // 指標陣列
    Student  *ptrs[Student_No] ;
    for ( i = 0 ; i < Student_No ; ++i ) ptrs[i] = &foo[i] ;

    // 使用指標排序
    cout << "> 依年齡排序 [大->小] " << endl ;
    sort( ptrs , ptrs+Student_No , by_age< greater<AGE> >() ) ;
    for ( i = 0 ; i < Student_No ; ++i ) cout << *ptrs[i] << '\n' ;
    cout << endl ;

    cout << "> 原始陣列順序 " << endl ;
    for ( i = 0 ; i < Student_No ; ++i ) cout << foo[i] << '\n' ;
    cout << endl ;

    return 0 ;
    
}
