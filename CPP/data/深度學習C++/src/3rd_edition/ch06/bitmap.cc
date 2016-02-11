#include <iostream>
#include <vector>

using namespace std ;

// 點矩陣文字
int  main() {
    
    int  i , j  , n  ;
    cout << "> 輸入中文字所對應的 8 個點矩數字 : " ;

    vector<int>    no(8) ;
    vector<bool>   bitmap(8) ;
    
    // 儲存文字點矩陣資料
    for ( i = 0 ; i < 8 ; ++i ) cin >> no[i] ;

    cout << endl ;
    
    // 迴圈重複每一行
    for ( i = 0 ; i < 8 ; ++i ) {
        
        n = no[i] ;

        // 將每一列的各個格子值存入 bitmap 矩陣中
        for ( j = 7 ; j >= 0 ; --j ) {
            bitmap[j] = n % 2 ;
            n /= 2 ;
        }
    
        // 列印每一列
        for ( j = 0 ; j < 8 ; ++j ) 
            cout << ( bitmap[j] ? " *" : "  " ) ;
        
        cout << endl ;
        
    }

    return 0 ;
    
}

                                 
