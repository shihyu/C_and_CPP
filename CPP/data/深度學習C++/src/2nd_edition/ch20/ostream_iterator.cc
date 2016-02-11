#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <list>

using namespace std ;

int main() {
    
    list<int>  foo ;
    ifstream   infile("data.db") ;
    istream_iterator<int>  in(infile) ;

    // 由 data.db 檔讀入資料一筆一筆插入串列 foo 的前端後印出
    copy( in , istream_iterator<int>() , front_inserter(foo) ) ;
    copy( foo.begin() , foo.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    return 0 ;
    
}







