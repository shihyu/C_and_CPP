#include <iostream>
#include <iomanip>

using namespace std ;

// 平方函式
template <class T>
T square( const T& i ) {  return ( i * i  ) ;  }

// 立方函式
template <class T>
T cubic( const T& i ) {  return ( i * i * i ) ; }

// 階乘函式
int factorial( int n ) {
    int  p = 1 ;
    for ( int i = 2 ; i <= n ; i++ )  p *= i ;
    return  p ;
}

// 變號
template <class T>
T  negative( const T& i ) { return  -i ; }

// 複製陣列 : 將 a 陣列的前 S 個元素複製到 b 陣列
template <class T>
void  copy_array( const T a[] , T  b[] , int S ) {
    for ( int i = 0 ; i < S ; ++i ) b[i] = a[i] ;
}

// 轉換函式
template <class Function , class T>
void  transform ( Function f , T foo[] , int size ) { 
    for ( int i = 0 ; i < size ; ++i )  foo[i] = f( foo[i] ) ;
}

// 列印陣列 : 
template <class T>
void  print_array( T array[] , int size , char *header = "" ) {
    cout << setw(8) << header << " :" ;
    for ( int i = 0 ; i < size ; ++i ) cout << setw(5) << array[i] ;
    cout << endl ;
}

int  main() {
    
    const int     S = 5 ;
    int        a[S] = { 1 , 2 , 3 , 4 , 5 } , b[S] ;

    print_array( a , S ,"原始陣列" ) ;

    // 平方 b 陣列的每個元素
    copy_array( a , b , S ) ;
    transform( square<int> , b , S ) ;
    print_array( b , S ,"平方" ) ;

    // 立方 b 陣列的每個元素
    copy_array( a , b , S ) ;
    transform( cubic<int> , b , S ) ;
    print_array( b , S , "立方" ) ;

    // 將 b 陣列每個元素變換正負號
    copy_array( a , b , S ) ;
    transform( negative<int> , b , S ) ;
    print_array( b , S , "變號" ) ;

    // 將 b 陣列的每個元素改換為其階乘值
    copy_array( a , b , S ) ;
    transform( factorial , b , S ) ;
    print_array( b , S , "階乘" ) ;

    return 0 ;
    
}

