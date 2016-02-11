#include <iostream>
#include <cstdlib>   // 隨機函式 rand 與設定隨機函式初值的函式 srand
#include <ctime>     // 程式在執行時的時刻資料 time

using namespace std ;

int main() {

    // 以程式執行的時間來設定隨機函式的初始值
    srand( static_cast<unsigned int>(time(NULL)) ) ;
  
    // 產生十個 0 到 9 之間的隨機整數
    for ( int i = 0 ; i < 10 ; ++i ) cout << rand()%10 << ' ' ;
    cout << '\n' ;

    return 0 ;
    
}
