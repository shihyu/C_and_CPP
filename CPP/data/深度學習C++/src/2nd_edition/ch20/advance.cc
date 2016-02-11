#include <iostream>
#include <iterator>
#include <list>
#include <string>

using namespace std ;

int main() {

    string                Q = "Must you be so linear, Jean-Luc" ;
    list<char>            startrek(Q.begin(),Q.end()) ;
    list<char>::iterator  itr1 , itr2 ;
 
    // itr1 與 itr2 都指向初始的位置
    itr1 = itr2 = startrek.begin() ;

    // itr1 與 itr2 分別往後前進 5 與 12 個字元後印出
    advance(itr1,5) ;
    advance(itr2,12) ;
    cout << *itr1 << " "  << *itr2 << endl ;
    
    // 計算兩者之間的字元數
    cout << distance(itr1,itr2) << endl ;

    return 0 ;
    
}

    
    
