#include <iostream>
#include <string>

using namespace std ;

// 定義 Weekday 列舉型別
enum  Weekday { Sun , Mon , Tue , Wed , Thu , Fri , Sat } ;

// 格式處理類別
class  Alpha_Weekday {
  private :

    static const string  weekday[7] ;   // 儲存列舉型別對應的字串
    istream  *inptr ;                   // 指標指向 istream 物件
    ostream  *outptr ;                  // 指標指向 ostream 物件

  public :

    // 處理資料的輸入
    friend Alpha_Weekday operator>> ( istream& , Alpha_Weekday ) ;
    friend istream&    operator>> ( Alpha_Weekday , Weekday& ) ;

    // 處理資料的輸出
    friend Alpha_Weekday operator<< ( ostream& , Alpha_Weekday ) ;
    friend ostream&    operator<< ( Alpha_Weekday , Weekday ) ;
    
} ;

const string Alpha_Weekday::weekday[7] = { "Sun" , "Mon" , "Tue" , 
                                           "Wed" , "Thu" , "Fri" , 
                                           "Sat" } ;


Alpha_Weekday  operator >> ( istream& in , Alpha_Weekday foo ) {
    foo.inptr = &in ;
    return  foo ;
}


istream&  operator >> ( Alpha_Weekday foo , Weekday& weekday ) {

    string  str ;
    *(foo.inptr) >> str ;
    
    for ( int i = 0 ; i < 7 ; ++i ) {
        if ( str == foo.weekday[i] ) {
            weekday = static_cast<Weekday>(i) ;
            break ;
        }
    }

    return  *(foo.inptr) ;
}


Alpha_Weekday  operator << ( ostream& out , Alpha_Weekday foo ) {
    foo.outptr = &out ;
    return  foo ;
}


ostream&  operator<< ( Alpha_Weekday foo , Weekday  weekday ) {
    *(foo.outptr) << foo.weekday[static_cast<int>(weekday)] ;
    return  *(foo.outptr) ;
}

// 定義格式處理器
Alpha_Weekday  alphaweekday ;

int main() {

    Weekday  weekday ;

    while ( 1 ) {
        cout << "輸入：" ;
        cin >> alphaweekday >> weekday ;
        cout << "輸出：" << weekday << endl ;
        cout << "輸出：" << alphaweekday << weekday << endl ;
    }
    
    return 0 ;
    
}

