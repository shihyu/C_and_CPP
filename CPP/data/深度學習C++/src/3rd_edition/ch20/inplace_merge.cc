#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std ;

// 比較個位數大小
bool  cmp_last_digit( int a , int b ) {
    return  a%10 < b%10 ;
}
    
int main() {
 
    const int S = 8 ;
    int  no[S] = { 23 , 15 , 28 , 11 , 44 , 26 , 17 , 9 };
    
    // 列印
    cout << "> 前後兩段合併前 : " ;
    copy( no , no+S , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 前後兩段合併
    inplace_merge( no , no+3 , no+S , cmp_last_digit ) ;

    // 列印
    cout << "> 前後兩段合併後 : " ;
    copy( no , no+S , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    return 0 ;
    
}

    
