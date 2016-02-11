#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>

using namespace std ;

// 比較十位數的大小
bool  big10 ( int a , int b ) {  return  a/10 < b/10 ; }


int main() {
    
    const int S = 18 ;
    int         old_no[S] ;
    deque<int>  no(S) ;
    
    // 產生 18 個個位數
    for ( int i = 0 ; i < S ; ++i ) old_no[i] = 4-(2*i)/10 ;
    
    cout << "> 排序前      : " ;
    copy( old_no , old_no+S , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 將 old_no 複製到 no 後用 sort 排序
    copy( old_no , old_no+S , no.begin() ) ;
    sort( no.begin() , no.end() ) ;
    cout << "> sort        : " ;
    copy( no.begin() , no.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 將 old_no 複製到 no 後用 stable_sort 排序
    copy( old_no , old_no+S , no.begin() ) ;
    stable_sort( no.begin() , no.end() ) ;
    cout << "> stable_sort : " ;
    copy( no.begin() , no.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl << endl ;

    // 將 old_no 複製到 no 後以比較十位數的方式使用 sort 排序
    copy( old_no , old_no+S , no.begin() ) ;
    sort( no.begin() , no.end() , big10 ) ;
    cout << "> sort        十位數 : " ;
    copy( no.begin() , no.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    // 將 old_no 複製到 no 後以比較十位數的方式使用 stable_sort 排序
    copy( old_no , old_no+S , no.begin() ) ;
    stable_sort( no.begin() , no.end() , big10 ) ;
    cout << "> stable_sort 十位數 : " ;
    copy( no.begin() , no.end() , ostream_iterator<int>(cout," ") ) ;
    cout << endl ;

    return 0 ;
    
}

