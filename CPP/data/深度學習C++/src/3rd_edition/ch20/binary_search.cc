#include <iostream>
#include <algorithm>

using namespace std ;

// 比較個位數大小
bool  cmp_last_digit( int a , int b ) {  return  a%10 < b%10 ; }

int main() {
    
    const int S = 10 ;

    // 依數字大小排序
    int  no1[S] = { 3 , 4 , 9 , 14 , 23 , 29 , 39 , 44 , 54 , 63 };
    
    int i ;

    cout << "請輸入搜尋的數字 : " ;
    
    // 搜尋輸入的數字是否在陣列中, 如果不是, 則重新讀取資料
    while( cin >> i ) {
        if ( binary_search( no1 , no1+S , i ) ) break ;
        cout << "> " << i << " 不在陣列中" << endl
             << "> 請再輸入新數字 : " ;
    }
    cout << "> " << i << " 已找到 -- 數字相同" << endl << endl ;

    // 依個位數大小排序, 使用 cmp_last_digit 比較函式來比較資料大小

    cout << "請輸入搜尋的數字 : " ;

    int  no2[S] = { 3 , 23 , 63 , 4 , 14 , 44 , 54 , 9 , 29 , 39 };
    while( cin >> i ) {
        if ( binary_search( no2 , no2+S , i , cmp_last_digit ) ) break ;
        cout << "> " << i << " 不在陣列中" << endl
             << "> 請再輸入新數字 : " ;
    }
    cout << "> " << i << " 已找到 -- 個位數相同" << endl ;

    return 0 ;
    
}
