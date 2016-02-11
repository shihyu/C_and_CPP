#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std ;

const int MAX_NO = 42 ;

// 產生一介於 [a,b] 之間的亂數
inline  int  random_no( int a , int b ) {

    return  rand()%(b-a+1) + a ;   

    // 或者使用以下較正確的方式產生亂數
    // return  a+static_cast<int>((b-a+1.)/(RAND_MAX+1.)*rand()) ;

}

// 對調 a 與 b 兩元素之值
inline  void  swap( int& a , int& b ) {
    int  tmp = a ;
    a = b ;
    b = tmp ;
}


// 產生 7 個介於 [1,42] 之間的樂透號碼, 最後一個為特別號碼
void  generate_lottery_number( int no[] , int n = 7 ) {

    int  i , j , tmp ;
    for ( i = 0 ; i < MAX_NO ; ++i ) no[i] = i+1 ;

    // 使用位置對調方式產生前 n 個樂透號碼 
    for ( i = 0 ; i < n ; ++i ) {
        
        // 隨機產生一欲對調元素的下標介於 [i,MAX_NO-1] 之間
        j = random_no(i,MAX_NO-1) ;

        // 如果 i 與 j 下標不同, 則對調 no[i] 與 no[j] 之值
        if ( i != j ) swap( no[i] , no[j] ) ;
        
    }

}

int main() {

    int i , j , n = 10 ;
    int no[MAX_NO] ;

    ofstream        outfile ;    
    ostringstream   outstring ;    

    // 設定亂數初值
    srand( static_cast<unsigned>( time(NULL) ) ) ;

    // 依次輸出 n 個檔案
    for ( i = 1 ; i <= n ; ++i ) {

        // 建構每次輸出的檔案名稱
        outstring << "lottery" << setfill('0') << setw(3) << i ;

        // 開啟檔案準備輸出
        outfile.open( outstring.str().c_str() ) ;

        // 產生樂透號碼
        generate_lottery_number(no) ;

        // 輸出中獎號碼到檔案
        for ( j = 0 ; j < 7 ; ++j ) outfile << setw(4) << no[j] ;
        outfile << endl ;

        // 關閉檔案
        outfile.close() ;

        // 將字串串流物件 sout 重新設為空字串
        outstring.str("") ;
    }

    return 0 ;
    
}

