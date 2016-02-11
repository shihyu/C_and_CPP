#include <iostream>
#include <set>

using  namespace  std ;

// 比較整數 i 的個位數是否比 j 的個位數小
struct  myless {
    bool operator() ( int i , int j ) { return ( i%10 < j%10 ) ; }
};

int main() {
    int  n ; 
    int no[10] = { 13 , 52 , 27 , 19 , 9 , 87 , 45 , 2 , 7 , 23 } ;

    // 將複集合與其iter更名以簡化名稱
    typedef   multiset<int,myless>  settype ;
    typedef   settype::iterator     setiter ;   

    // 定義複集合與相關iter
    settype  foo(no,no+10)     ;             
    setiter  i ;
    pair<setiter,setiter>  iter ;
    
    // 列印複集合所有元素
    for ( i = foo.begin() ; i != foo.end() ; ++i ) cout << *i << ' ' ;
    cout << "\n> "  ;
    
    // 搜尋元素，並印出所有相當的數字
    while ( 1 ) {
        cin >> n ;
        iter = foo.equal_range(n) ;  
        cout << "--> " ;

        if ( iter.first != iter.second ) 
            for ( i = iter.first ; i != iter.second ; ++i ) 
                cout << *i << ' ' ;
        else 
            cout << "沒有相當的元素" ;
        
        cout << "\n> " ;
    }
    return 0 ;
}
