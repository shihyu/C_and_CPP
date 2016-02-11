#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>

using namespace std ;

// abc:2 , def:3 , ghi:4 , jkl:5 , mno:6 , pqrs:7 , tuv:8 , wxyz:9
void  decoding( char& c ) {
    if ( c >= 'a' && c <= 'o' ) 
        c = ( c - 'a' ) / 3 + '2' ;
    else if ( c >= 'p' && c <= 's' ) 
        c = '7' ;
    else if ( c >= 't' && c <= 'v' ) 
        c = '8' ;
    else 
        c = '9' ;
}

int main() {
    
    string  phone = "startrek" ;
    cout << phone << " --> " ;
    
    // 將英文字轉為字元數字號碼
    for_each( phone.begin() , phone.end() , decoding ) ;

    // 列印字元數字號碼
    copy( phone.begin() , phone.end() , ostream_iterator<char>(cout,"") ) ;
    cout << endl ;

    return 0 ;
    
}
