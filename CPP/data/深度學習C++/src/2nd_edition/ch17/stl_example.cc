#include <iostream>
#include <vector>         // 使用向量陣列容器與迭代器
#include <algorithm>      // 使用排序演算函式         

using namespace std ;

// (4) 定義一函式物件類別 : 用以比較兩筆資料的個位數字大小
template <class T>
struct  Remainder {
    bool  operator() ( const T& a , const T& b ) const { 
        return  a%10 > b%10 ;
    }
} ;

// (5) 列印容器
template <class T>
void  print_container( const T& iter1 , const T& iter2 , char *sep ) {
    for ( T itr = iter1 ; itr != iter2 ; ++itr ) cout << *itr << sep ;
} 

int  main() {
    
    // (1) 定義一個可以儲存 20 個整數的向量陣列容器
    vector<int>  foo(20) ;          

    // (2) 定義一個針對整數向量陣列的iter物件
    vector<int>::iterator  itr ;   

    // 利用iter物件將整數 1 到 20 一一的存入此向量陣列中
    int  no = 1 ;
    for ( itr = foo.begin() ; itr != foo.end() ; ++itr ) *itr = no++ ;

    // (3) 利用排序演算函式將向量陣列元素依個位數的大小由大至小重作排序
    sort( foo.begin() , foo.end() , Remainder<int>() ) ;

    // (5) 利用函式將向量陣列印出，且元素之間以一空白分開
    print_container( foo.begin() , foo.end() , " " ) ;
    cout << endl ;

    return 0 ;
   
}
