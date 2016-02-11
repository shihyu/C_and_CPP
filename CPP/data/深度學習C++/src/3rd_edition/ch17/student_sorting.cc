#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <algorithm>

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
    
    NAME    get_name()   const {  return name ;   }
    AGE     get_age()    const {  return age ;    }
    GENDER  get_gender() const {  return gender ; }

    friend  ostream& operator << ( ostream& out , 
                                   const Student& foo ) ;

};

// 輸出學生資料
ostream& operator << ( ostream& out , const Student& foo ) {
    return  out << "姓名 : " << setw(6) << foo.name.c_str() 
                << " [" << ( foo.gender == female ? 'F' : 'M' )
                << "]"  << setw(5) << " 年齡 : " << foo.age  ;
}

// 函式類別 : 比較名稱  (比較的方式設定成樣板型別參數)
template <class Compare>
struct  by_name {
    bool operator() ( const Student& a , const Student& b ) const {
        return  Compare()( a.get_name() , b.get_name() ) ;
    }
};

// 函式類別 : 比較年齡 (比較的樣板型別參數內定為 less<AGE>)
template <class  Compare = less<AGE> >
struct  by_age {
    bool operator() ( const Student& a , const Student& b ) const {
        return  Compare()( a.get_age() , b.get_age() ) ;
    }
};

// 樣板函式 : 比較性別  (比較的方式設定成樣板型別參數)
template <class Compare>
bool  by_gender ( const Student& a , const Student& b ) {
    return  Compare()( a.get_gender() , b.get_gender() ) ;
}

// 函式類別 : 先比較性別, 再比較年齡, 最後比較姓名
template <class Compare_g , class Compare_a , class Compare_n>
struct  my_rule {
    bool operator() ( const Student& a , const Student& b ) const {
        if ( a.get_gender() == b.get_gender() ) {
            
            if ( a.get_age() ==  b.get_age() ) 
                return  Compare_n()( a.get_name() , b.get_name() ) ;
            else 
                return  Compare_a()( a.get_age() , b.get_age() ) ;

        } else 
            return Compare_g()( a.get_gender() , b.get_gender() ) ;
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

    cout << "> 依姓名排序 [小->大] " << endl ;
    sort( foo , foo+Student_No , by_name< less<NAME> >() ) ;
    for ( i = 0 ; i < Student_No ; ++i )  cout << foo[i] << '\n' ;
    cout << endl ;

    cout << "> 依年齡排序 (使用內定排序方式[小->大]) " << endl ;
    sort( foo , foo+Student_No , by_age<>() ) ;
    for ( i = 0 ; i < Student_No ; ++i )  cout << foo[i] << '\n' ;
    cout << endl ;

    cout << "> 依性別排序 [大->小] " << endl ;
    sort( foo , foo+Student_No , by_gender< greater<GENDER> > ) ;
    for ( i = 0 ; i < Student_No ; ++i )  cout << foo[i] << '\n' ;
    cout << endl ;

    cout << "> 依下列方式順序排序\n"
         << "  (1) 性別 [小->大] (2) 年齡 [大->小] " 
         << "(3) 姓名 [小->大]\n";    
    sort( foo , foo+Student_No ,
          my_rule< less<GENDER>, greater<AGE> , less<NAME> >() ) ;
    for ( i = 0 ; i < Student_No ; ++i )  cout << foo[i] << '\n' ;
    cout << endl ;

    return 0 ;
    
}
