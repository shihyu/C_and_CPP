#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>

using namespace std ;

// 比較十位數的大小
bool  big10 ( int a , int b ) {  return  a/10 < b/10 ; }

int main() {
    
    const int S = 6 ;
    int         old_no[S] = { 16 , 9 , 36 , 4 , 25 , 1 } ;
    deque<int>  no(S) ;
    
    cout << "> 排序前                    : " ;
    copy( old_no , old_no+S , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 將 old_no 複製到 no 後用 partial_sort 一個個依次排序
    for ( int  i = 1 ; i <= no.size() ; ++i ) {
        copy( old_no , old_no+S , no.begin() ) ;
        partial_sort( no.begin() , no.begin()+i , no.end() ) ;
        cout << "> partial sort        ( " << i << " ) : " ;
        copy( no.begin() , no.end() , ostream_iterator<int>(cout," ") ) ;
        cout << endl ;
    }
    
    cout << endl ;
    
    // 將 old_no 複製到 no 後以比較十位數的方式
    // 使用 partial_sort 一個個依次排序
    for ( int  i = 1 ; i <= no.size() ; ++i ) {
        copy( old_no , old_no+S , no.begin() ) ;
        partial_sort( no.begin() , no.begin()+i , no.end() , big10 ) ;
        cout << "> parital sort 十位數 ( " << i << " ) : " ;
        copy( no.begin() , no.end() , ostream_iterator<int>(cout," ") ) ;
        cout << endl ;
    }

    return 0 ;
    
}

