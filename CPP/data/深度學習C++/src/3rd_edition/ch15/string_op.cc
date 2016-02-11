#include <iostream>
#include <string>

using namespace std ;

// 字串重複 n 次
string  operator* ( const string& foo , unsigned int n ) {
    string  tmp = foo ;
    for ( int i = 1 ; i < n ; ++i ) tmp += foo ;
    return  tmp ;
}

// 字串重複 n 次
string&  operator*= ( string& foo , unsigned int n ) {
    return  foo = foo * n ;
}

// 由字串 foo 中去除 str
string  operator- ( const string& foo , const string& str ) {

    string  tmp = foo ;
    int i = 0 ;

    while ( i < tmp.length() ) {           
        i = tmp.find( str , i ) ;          // 找尋字串
        if ( i == string::npos ) break ;   // 若找不到字串則跳離迴圈
        tmp.erase( i , str.length() ) ;    // 刪除字串
    }
    return  tmp ;
}

// 由字串 foo 中去除 str
string&  operator-= ( string& foo , const string& str ) {
    return  foo = foo - str ;
}

int main() {
    
    string  DNA = "TGCA" ;
    
    DNA *= 2 ;
    DNA = DNA + "TT" + DNA + "TT" ;
    cout << "DNA : " << DNA << "\n\n" ;
    
    DNA -= "CAT" ;
    cout << "DAN : " << DNA << endl ;

    return 0 ;
    
}
