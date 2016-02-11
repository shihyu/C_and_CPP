#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <ctime>

using namespace std ;

void  swap( int& a , int& b ) {
    int t = a ;  a = b ;  b = t ;
}


int main() {

    // 以時間設定亂數初值
    srand( time(NULL) ) ;
    
    // 電腦產生樂透中獎號碼
    int  i , no[42] ;
    for ( i = 0 ; i < 42 ; ++i ) no[i] = i+1 ;
    for ( i = 0 ; i < 6 ; ++i ) swap(no[i], no[rand()%42])  ;

    vector<int>  lottery(6) ;
    copy( no , no+6 , lottery.begin() ) ;
    
    cout << "> 樂透開獎號碼 : " ;
    copy( lottery.begin() , lottery.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 人工輸入彩券號碼
    vector<int>  foo ;
    cout << "> 彩券購買號碼 : " ;
    copy( istream_iterator<int>(cin) , istream_iterator<int>() ,
          back_inserter(foo) ) ;

    // 核算中獎的號碼其及總數
    vector<int>::iterator  iter = foo.begin() ;
    vector<int>            matched_no ;
    
    while( ( iter = find_first_of( iter , foo.end() , lottery.begin() ,
                                   lottery.end() ) ) != foo.end() ) {
        matched_no.push_back( *iter++ ) ;
    }
    
    cout << "> 彩券中獎號碼 : " ;
    copy( matched_no.begin() , matched_no.end() , 
          ostream_iterator<int>(cout," ") ) ;
    cout << " , 共 " <<  matched_no.size() << " 個號碼" << endl ;
    
    
}

    
    
