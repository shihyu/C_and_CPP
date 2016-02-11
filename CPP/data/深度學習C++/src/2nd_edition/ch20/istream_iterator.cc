#include <iostream>
#include <iterator>

using namespace std ;

int main() {

    // 針對 cin 產生一輸入緩衝區迭代器
    istream_iterator<int>  iter(cin) ;
    
    int  sum ;

    // 連續做加法動作  直到輸入的數字比 1 小為止
    for ( sum = 0  ; *iter >= 0 ; iter++ ) sum += *iter ;
    cout << sum << endl ;

    return 0 ;
    
}
