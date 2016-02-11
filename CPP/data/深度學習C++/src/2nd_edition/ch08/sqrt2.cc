#include <iostream>
#include <vector>
#include <cmath>             // 根號函式 
#include <iomanip>

using namespace std ;

double  r( const vector<int>& a , int i ) {

    int  n = a.size()-1 ;

    if ( i == 0 )
        return  a[n] ;
    else 
        return  a[n-i] + 1./r(a,i-1) ;

}

int main() {

    double  approx ;                     // 儲存估算值
    double  sqrt2 = sqrt(2.) ;           // 計算根號 2
    
    cout << "> 連分數估算 sqrt(2) : \n" ;
    
    for ( int i = 0 ; i <= 15 ; ++i ) {

        vector<int>  a(i+1,2) ;          // 設定連分數係數
        a[0] = 1 ;                       // 第一個元素改為 1

        approx = r(a,i) ;                // 連分數估算 

        cout << "c_" << left << setw(2) << i << " : " 
             << fixed << setw(10) << approx 
             << "  誤差 : " << right << scientific 
             << setw(14) << sqrt2-approx << endl ;

    }
    
    return 0 ;
    
}
