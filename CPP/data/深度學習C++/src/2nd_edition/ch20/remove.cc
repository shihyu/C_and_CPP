#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>
#include <vector>

using namespace std ;

// 檢查是否為偶數
bool  even( int a ) { return a % 2 == 0 ; }

int main() {
    
    const int S = 8 ;
    int n[S] = { 23 , 45 , 24 , 87 , 76 , 10 , 24 , 55 };

    list<int>                no(n,n+S) ;
    list<int>::iterator      iter1 ;
    
    vector<int>              foo ;
    vector<int>::iterator    iter2 ;

    // 列印原始串列
    cout << "> 原始元素 : " ;
    copy(no.begin(),no.end(),ostream_iterator<int>(cout," ")) ;
    cout << endl ;

    // 搬移 24
    iter1 = remove( no.begin() , no.end() , 24 ) ;
    
    // 列印剩餘元素
    cout << "> 搬移 24  : " ;
    copy(no.begin(),iter1,ostream_iterator<int>(cout," ")) ;
    cout << endl ;

    // 重新設定 no 
    copy(n,n+S,no.begin()) ;

    // 將偶數搬移
    cout << "> 搬移偶數 : " ;
    iter1 = remove_if( no.begin() , no.end() , even ) ;

    // 列印剩餘元素
    copy(no.begin(),iter1,ostream_iterator<int>(cout," ")) ;
    cout << endl ;

    // 重新設定 no 
    copy(n,n+S,no.begin()) ;

    // 搬移 24  並將剩餘元素複製到 foo
    remove_copy( no.begin() , no.end() , back_inserter(foo) , 24 ) ;
    
    // 列印 foo
    cout << "> 搬移 24  : " ;
    copy(foo.begin(),foo.end(),ostream_iterator<int>(cout," ")) ;
    cout << endl ;

    // 重新設定 foo 與 no
    copy(n,n+S,no.begin()) ;
    foo.resize(no.size()) ;

    // 將偶數搬移 並將剩餘元素複製到 foo
    iter2 = remove_copy_if( no.begin() , no.end() , foo.begin() , even ) ;
    
    // 列印 foo
    cout << "> 搬移偶數 : " ;
    copy(foo.begin(),iter2,ostream_iterator<int>(cout," ")) ;
    cout << endl ;

    return 0 ;
    
}

    
