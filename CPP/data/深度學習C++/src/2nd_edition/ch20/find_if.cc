#include <iostream>
#include <algorithm>
#include <string>

using namespace std ;

struct  vowel {
    bool  operator()( char c ) const {
        return ( c == 'a' || c == 'e' || c == 'i' ||
                 c == 'o' || c == 'u' ) ? true : false ;
    }
};

int main() {

    string  Q = "My exact words were dangerous savage child race." ;

    int               count = 0 ;
    string::iterator  iter = Q.begin() ;

    while ( ( iter = find( iter , Q.end() , 'a' ) ) != Q.end() ) {
        ++count ; ++iter ;
    }
    cout << "共有 " << count << " 個 a 字母 " << endl ;
    
    count = 0 ;
    iter = Q.begin() ;
    while ( ( iter = find_if( iter , Q.end() , vowel() ) ) != Q.end() ) {
        cout << *iter++ ; count++ ;
    }
    cout << " : 共有 " << count << " 個母音 " << endl ;

    return 0 ;
    
}

    
    
    
