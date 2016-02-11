#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std ;

int main() {

    const int  S = 5 ;
    double     no[S] = { 3.5 , -2 , 5.75 , -4 , 8.25 };

    // 開啟檔案準備輸出
    ofstream                   outfile("number.db",ios::out) ;
    ostreambuf_iterator<char>  out(outfile) ;

    // 字元指標 p 指向 no 陣列的起始
    char *p = reinterpret_cast<char*>(no) ;

    // 以字元的方式直接將 no 陣列輸出到檔案 number.db
    // number.db 為二進位檔
    copy( p , p + S * sizeof(double) , ostreambuf_iterator<char>(out) ) ;

    outfile.close() ;


    // 開啟檔案準備讀入
    ifstream                   infile("number.db",ios::in) ;
    istreambuf_iterator<char>  in(infile) ;

    double  no2[S] ;
    
    // 字元指標 p 指向 no2 陣列的起始
    p = reinterpret_cast<char*>(no2) ;

    // 以字元的方式直接將檔案 number.db 的資料存入 no2 陣列內
    copy( in , istreambuf_iterator<char>() , p ) ;

    // 列印 no2 陣列
    copy( no2 , no2+S , ostream_iterator<double>(cout,"  ") ) ;
    cout << endl ;

    return 0 ;

}

