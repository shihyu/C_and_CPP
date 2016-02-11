#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std ;

int main() {

    // 固定式設定樂透開獎號碼 : 32 24 38 42 12 19
    int  lottery[6] = { 32 , 24 , 38 , 42 , 12, 19 } ;
    
    // 列印樂透開獎號碼
    cout << "> 樂透開獎號碼 : " ;
    copy( lottery , lottery+6 , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 人工輸入彩券號碼
    vector<int>  no ;
    cout << "> 彩券購買號碼 : " ;
    copy( istream_iterator<int>(cin) , istream_iterator<int>() ,
          back_inserter(no) ) ;

    // 核算中獎的號碼其及總數
    vector<int>::iterator  iter = no.begin() ;
    vector<int>            matched_no ;
    
    while( ( iter = find_first_of( iter , no.end() , lottery ,
                                   lottery+6 ) ) != no.end() ) {
        matched_no.push_back( *iter++ ) ;
    }
    
    // 列印彩券中獎號碼
    cout << "> 彩券中獎號碼 : " ;
    copy( matched_no.begin() , matched_no.end() , 
          ostream_iterator<int>(cout," ") ) ;
    cout << " , 共 " <<  matched_no.size() << " 個號碼" << endl ;

    return 0 ;
    
}

    
    
