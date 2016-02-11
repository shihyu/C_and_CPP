#include <iostream>
#include <fstream>
#include <iterator>

using namespace std ;

struct  to_upper {
    char  operator() ( char c ) const {
        return ( c >= 'a' && c <= 'z' ? c - 'a' + 'A' : c ) ;
    }
};

// S 與 T 為迭代器類別, Fn 為函式物件類別
template <class S , class T , class Fn>
void  convert( S i1 , S i2 , T i3 , Fn fn ) {
    for ( S i = i1 ; i != i2 ; i++ , i3++ )  *i3 = fn( *i ) ;
}

int main() {

    ifstream                   infile("episodes.db",ios::in) ;
    ofstream                   outfile("EPISODES.db",ios::out) ;
    
    istreambuf_iterator<char>  in(infile) ;
    ostreambuf_iterator<char>  out(outfile) ;
    
    // 將 episodes 檔案內所有英文字母轉成大寫後存入 EPISODES 檔
    convert( in , istreambuf_iterator<char>() , out , to_upper() ) ;

    return 0 ;

}

