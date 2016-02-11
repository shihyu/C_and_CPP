#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std ;

// 檢查字元是否為母音
bool  vowel ( char c ) {
    return ( c == 'a' || c == 'e' || c == 'i' ||
             c == 'o' || c == 'u' ) ? true : false ;
}

int main() {

    string  enterprise = "To boldly go where no one has gone before" ;
    string  startrek , tng ;

    startrek = enterprise ;

    // 用橫線取代所有的空格
    replace( startrek.begin() , startrek.end() , ' ' , '-' ) ;
    cout << "1 > " << startrek << endl ;

    startrek = enterprise ;

    // 用橫線取代所有的空格  但結果插入到新字串
    replace_copy( startrek.begin() , startrek.end() , back_inserter(tng) , 
                  ' ' , '-' ) ;
    cout << "2 > " << startrek << endl << "--> " << tng << endl ;

    startrek = enterprise ;

    // 將所有的母音用星號取代
    replace_if( startrek.begin() , startrek.end() , vowel , '*' ) ;
    cout << "3 > " << startrek << endl ;

    tng = "" ;
    startrek = enterprise ;

    // 將所有的母音用星號取代  結果插入到新字串
    replace_copy_if( startrek.begin() , startrek.end() , back_inserter(tng) , 
                     vowel , '*' ) ;
    cout << "4 > " << startrek << endl << "--> " << tng << endl ;

    return 0 ;
    
}
