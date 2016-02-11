#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <ctime>

using namespace std ;

// 產生一 [0,n) 的亂數
int  random_number ( int n ) { return rand() % n ; }

int main() {
    
    // 將 1 到 42 個整數依次存入 no 陣列內
    const int S = 42 ;
    int   no[S] ;
    for ( int i = 0 ; i < S ; ++i ) no[i] = i+1 ;

    // 設定亂數種子初值
    srand( static_cast<unsigned>(time(NULL)) ) ;
    
    // 將此陣列元素重新分配位置
    random_shuffle( no , no+S , random_number ) ;

    // 輸出前六個元素
    copy( no , no+6 , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    return 0 ;

}


            
