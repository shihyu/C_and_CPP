#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std ;

// 比較字串長度
bool  ssize( const string& a , const string& b ) {
    return  a.size() < b.size()  ;
}

int main() {
    
    const int S = 8 ;
    string  Picard[S] = { "I" ,  "am" ,  "Locutus" ,  "of" ,  
                          "Borg" ,  "Resistance" , "is" ,  "futile" } ;

    vector<string>  Locutus ;
    
    // 將 Picard 字串陣列依字串長度由小到大排列複製到 Locutus
    for ( int i = 1 ; i <= S ; ++i ) {
        // 重新設定 Locutus 的長度
        Locutus.resize(i) ;
        partial_sort_copy( Picard , Picard+S , 
                           Locutus.begin() , Locutus.end() , ssize ) ;
        copy( Locutus.begin() , Locutus.begin()+i , 
              ostream_iterator<string>(cout," ") ) ;
        cout << endl ;
    }
    cout << "> 原始字串陣列 : " ;
    copy( Picard , Picard+S , ostream_iterator<string>(cout," ") ) ;
    cout << endl ;

    return 0 ;
    
}

    
