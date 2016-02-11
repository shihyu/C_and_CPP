#include <iostream>
#include <iterator>

using namespace std ;

struct  to_upper {
    char  operator() ( char c ) const {
        return ( c >= 'a' && c <= 'z' ? c - 'a' + 'A' : c ) ;
    }
};

// S 與 T 為\iter類別, Fn 為函式物件類別
template <class S , class T , class Fn>
void  convert( S i1 , S i2 , T i3 , Fn fn ) {
    for ( S i = i1 ; i != i2 ; i++ , i3++ )  *i3 = fn( *i ) ;
}

int main() {

    istreambuf_iterator<char>  in(cin) ;
    ostream_iterator<char>     out(cout) ;
    
    // 將輸入的英文句子內的所有英文字母轉成大寫後輸出
    convert( in , istreambuf_iterator<char>() , out , to_upper() ) ;

    return 0 ;

}

