#include <iostream>
#include <cstdlib>   // 提供隨機函式 rand 與設定隨機函式
                     // 初值的函式 srand
#include <ctime>     // 提供程式在執行時的時刻資料 time

using namespace std ;

int main() {

    int  foo[] = { 2 , 4 , 6 , 8 , 10 };
    int  i , j , tmp ;

    // 以時間設定隨機函式初始值
    srand( static_cast<unsigned>( time(NULL) ) ) ;

    // 計算整數陣列的長度
    int  size = sizeof(foo) / sizeof(int) ;
    
    // 陣列元素由後往前依次與其前的另一個隨機位置對調數值
    for ( i = size-1 ; i > 0 ; --i ) {
        j      = rand() % (i+1) ;
        if ( i == j ) continue ;  // 如果 i 與 j 兩位置相等則不對調
        tmp    = foo[i] ;
        foo[i] = foo[j] ;
        foo[j] = tmp ;
    }
    
    for ( i = 0 ; i < size ; ++i )  cout << foo[i] << " " ;
    cout << '\n' ;
    
    return 0 ;
    
}
