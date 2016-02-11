#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std ;

struct  string_length {
    bool  operator() ( const string& a , const string& b ) const {
        return  a.size() < b.size() ;
    }
};

int main() {
    
    const  int S = 6 ;
    string startrek[S] = { "where" , "no" , "one" , "has" , "gone" , "before" };
    string tng[S] ;

    cout << "原始 : " ;
    copy( startrek , startrek+S , ostream_iterator<string>(cout," ") ) ;
    cout << endl ;
    
    // 比較字元順序
    for ( int i = 0 ; i < S ; ++i ) {
        copy( startrek , startrek+S , tng ) ;
        nth_element( tng , tng+i , tng+S ) ;
        cout << "  " << i << "  : " ;
        copy( tng , tng+S , ostream_iterator<string>(cout," ") ) ;
        cout << endl ;
    }

    cout << endl ;
    
    // 以字串長度比較
    for ( int i = 0 ; i < S ; ++i ) {
        copy( startrek , startrek+S , tng ) ;
        nth_element( tng , tng+i , tng+S , string_length() ) ;
        cout << "  " << i << "  : " ;
        copy( tng , tng+S , ostream_iterator<string>(cout," ") ) ;
        cout << endl ;
    }

    return 0 ;
    
}
