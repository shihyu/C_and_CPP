#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std ;

// 拆解記錄字串 foo 成細目字串陣列 bar, 記錄的分離標記為 sep
void  split_string( const string& foo , const string& sep ,
                    string  bar[] ) {
    
    // i , j 為下標, n 為細目下標
    int  i = 0 , j , n = 0 ;

    while ( 1 ) {

        // foo 由下標 i 找分離標記 sep
        j = foo.find(sep,i) ;

        // 若已經找不到分離標記, 則存入最後一筆細目後離開
        if ( j == string::npos ) {
            bar[n] = foo.substr(i,(foo.length()-i)) ;
            return ;
        }
        
        // 儲存記錄的細目
        bar[n] = foo.substr(i,(j-i)) ;
        ++n ;

        // 計算下次找尋的下標值
        i = j + sep.length() ;
        
    }
    
}


// 列印記錄的細目資料
void  print_student_record( const string field[] ) {

    cout << "> 姓名 : " << field[0] << "  "
         << setw(10) << "性別 : " << field[1] << "  "
         << setw(10) << "出生 : " << field[2] << '\n' 
         << "  學號 : " << setw(6) << setfill('0') 
         << field[3].c_str() << setfill(' ') << "  " 
         << setw(10) << "入學 : " << field[4] << '\n'
         << "  住址 : " 
         << ( field[5] == "*" ? "缺" : field[5] ) << '\n'
         << "  電話 : " 
         << ( field[6] == "*" ? "缺" : field[6] ) << "\n\n" ;

}


int  main() {
    
    const int FIELD_NO = 7 ;

    // 開啟資料檔案
    ifstream  infile( "student.db" ) ;
    
    string  record ;
    string  field[FIELD_NO]  ;

    // 每次由資料檔中讀取一行資料後分解, 列印
    while ( getline( infile , record ) ) {
        if ( record == "" ) break ;
        split_string( record , "::" , field ) ;
        print_student_record( field ) ;
    }

    infile.close() ;
    
    return 0 ;
    
}
