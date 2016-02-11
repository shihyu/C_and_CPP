#include <iostream>
#include <iomanip>           

using namespace std ;

int main() {
    
    int  i , j , no ;
    
    // a , b 分別為巴斯卡三角形的上一列與下一列陣列
    int  a[20] , b[20] ;
    
    cout << "> 輸入巴斯卡三角形的高度 : " ;
    cin >> no ;
        
    a[0] = 1 ;
        
    for ( i = 0 ; i < no ; ++i ) {

        // 列印巴斯卡第 i 列陣列
        cout << setw(3*(no-i)) << " " ;
        for ( j = 0 ; j <= i ; ++j ) cout << setw(6) << a[j] ;
        cout << endl ;
            
        // 計算下一列陣列值
        b[0] = 1 ;
        for ( j = 1 ; j <= i ; ++j ) b[j] = a[j-1] + a[j] ;
        b[i+1] = 1 ;
            
        // 重新設定上一列的陣列
        for ( j = 0 ; j <= i+1 ; ++j ) a[j] = b[j] ;
            
    }
        
    return 0 ;
    
}
