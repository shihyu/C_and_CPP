#include <iostream>
#include <algorithm>

using namespace std ;

// 兩數是否同為奇數或者是偶數
bool  odd_even( int a , int b ) {  return a%2 == b%2 ; }

int  main() {

    const int S1 = 10 , S2 = 7 ;

    // 定義 資料庫 與 樣品 陣列
    int  databank[S1] = { 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 0 };
    int  sample[S2]    = { 8 , 6 , 7 , 8 , 9 , 0 , 3 };

    int   i , j , len , *p ;

    // 列印資料庫
    cout << "> databank : " ;
    for ( i = 0 ; i < S1 ; ++i ) cout << databank[i] << " " ;
    cout << endl << endl ;

    // 在資料庫序列內找尋到樣品內最長的資料序列
    for ( len = S2 ; len > 0 ; --len ) {
        for ( i = 0 ; i+len <= S2 ; ++i ) {

            // 列印所要找尋的樣品子序列
            cout << "> 找尋序列 : " ;
            for ( j = i ; j < i+len ; ++j ) cout << sample[j] << " " ;
            cout << endl ;

            // 在資料庫序列內找尋 sample[i] 到 sample[i+len-1] 子序列
            p = search( databank , databank+S1 , sample+i , 
                        sample+i+len ) ;
            
            /*********************************************************
            // 在資料庫序列內找尋 sample[i] 到 sample[i+len-1] 子序列
            // 找尋條件為同為奇數或偶數
            // 
            p = search( databank , databank+S1 , sample+i , 
                        sample+i+len , odd_even ) ;
            **********************************************************/

            // 若已找到, 則列印後跳離整個迴圈
            if ( p != databank+S1 ) {
                cout << "> 已在資料庫內找到樣品內最長子序列 : " ;
                for ( j = 0 ; j < len ; ++j ) cout << *(p+j) << " " ;
                goto  NEXT ;
            }
        }
    }
    
    cout << "> 資料庫序列內不包含樣品的任何子序列 ! "  ;
    
    NEXT :  
        cout << endl << endl ;
    
    // 在資料庫序列中找尋樣品內最長的資料序列
    // 滿足同為奇數或偶數的條件
    for ( len = S2 ; len > 0 ; --len ) {
        for ( i = 0 ; i+len <= S2 ; ++i ) {

            // 列印所要找尋的樣品子序列
            cout << "> 找尋序列 : " ;
            for ( j = i ; j < i+len ; ++j ) cout << sample[j] << " " ;
            cout << endl ;

            // 在資料庫序列內找尋 sample[i] 到 sample[i+len-1] 子序列
            // 找尋條件為同為奇數或偶數
            p = search( databank , databank+S1 , sample+i , 
                        sample+i+len , odd_even ) ;

            if ( p != databank+S1 ) {
                cout << "> 已在資料庫中找到樣品內最長子序列 : " ;
                for ( j = 0 ; j < len ; ++j ) cout << *(p+j) << " " ;
                cout << endl ;
                return 0 ;
            }
        }
    }
    
    cout << "> 資料庫序列內不包含樣品的任何子序列 ! "  ;
    cout << endl ;

    return 0 ;
    
}

    
    
    
    
