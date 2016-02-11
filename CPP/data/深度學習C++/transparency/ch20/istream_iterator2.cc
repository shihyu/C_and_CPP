#include <iostream>
#include <iterator>

using namespace std ;

int main() {

    istream_iterator<int>  iter(cin) ;
    
    int  sum ;
    // 連續做加法動作  直到輸入檔案終結字元為止
    for ( sum = 0  ; iter != istream_iterator<int>() ; iter++ )
        sum += *iter ;

    cout << "輸入整數總和 = " << sum << endl ;

    return 0 ;
    
}
