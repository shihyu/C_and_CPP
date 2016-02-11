#include <iostream>
#include <assert.h>

using namespace std ;

class  Vector {

  private :
    int  *data ;  // 向量元素
    int   size ;  // 向量元素個數

  public :
    // 內定建構函式
    Vector() : data(NULL) , size(0) {};

    // 建構函式
    Vector( unsigned int s , int v = 0 ) ;

    // 複製建構函式
    Vector( const Vector& foo ) ;

    // 指定運算子
    Vector&  operator = ( const Vector& foo ) ;

    // 解構函式
    ~Vector() {  delete [] data ;  }

    // 向量長度
    int  length() const { return size ;  }
        
    // 下標函式
    int&        operator [] ( int i )       { return data[i] ; }
    const int&  operator [] ( int i ) const { return data[i] ; }

    // 輸入運算子
    friend istream& operator >> ( istream& in  , Vector& foo ) ;

    // 輸出運算子
    friend ostream& operator << ( ostream& out , 
                                  const Vector& foo ) ;
    
};

// 建構函式 : 請留意 v 整數在此不寫預設值
Vector::Vector( unsigned int s , int v ) : size(s) {
    data = new int[size] ;
    for ( int i = 0 ; i < size ; ++i ) data[i] = v ;
}

// 複製建構函式
Vector::Vector( const Vector& foo ) : size(foo.size) {
    data = new int[size] ;
    for ( int i = 0 ; i < size ; ++i ) data[i] = foo.data[i] ;
}

// 指定運算子
Vector&  Vector::operator=( const Vector& foo ) {
    if ( this == &foo ) return  *this ;
    if ( foo.size != size ) { 
        delete [] data ; 
        size = foo.size ; 
        data = new int[size] ;
    }
    for ( int i = 0 ; i < size ; ++i ) data[i] = foo.data[i] ;
}

// 加法
Vector  operator+( const Vector& foo , const Vector& bar ) {
    Vector  tmp(foo.length()) ;
    for ( int i = 0 ; i < tmp.length() ; ++i ) 
        tmp[i] = foo[i] + bar[i] ;
    return tmp ;
}

// 內積
int  operator*( const Vector& foo , const Vector& bar ) {
    int  sum = 0 ;
    for ( int i = 0 ; i < foo.length() ; ++i ) 
        sum += foo[i] * bar[i] ;
    return sum ;
}

// 輸入運算子
istream&  operator>> ( istream& in , Vector &foo ) {
    for ( int i = 0 ; i < foo.size ; ++i ) in >> foo[i] ;
    return  in ;
}

// 輸出運算子
ostream&  operator<< ( ostream& out , const Vector &foo ) {
    cout << '(' << ' ' ;
    for ( int i = 0 ; i < foo.size ; ++i ) out << foo[i] << ' ' ;
    cout << ')' ;
    return  out ;
}

int  main() {
    
    // 建構函式
    Vector  a(3,1) , b(3,4) , c(3) ;
    
    // 輸出運算子
    cout << "> a = " << a << " , b = " << b << endl ;
    
    // 加法 與 內積
    cout << ">  a + b = " << a + b << " ,"
         << "  a * b = " << a * b << endl << endl ;

    // 向量輸入運算子
    cout << "> 輸入 3 筆整數資料 : " ;
    cin  >> c ;
    cout << "> c = " << c << endl << endl ;

    // 複製建構函式
    Vector  d(c) ;
    cout << "> d(c)  ==>  d = " << d << endl ;

    // 加法與指定函式
    d = a + b + c ;
    cout << "> d = a + b + c  ==>  d = " << d << endl << endl ;

    // 向量陣列
    Vector  foo[3] ;    // 呼叫內定建構函式

    foo[0] = a ;    foo[1] = b ;    foo[2] = c ;
    
    int  i ;
    cout << "> " ;
    for ( i = 0 ; i < 3 ; ++i ) 
        cout << "[" << i << "] = " << foo[i] << "  " ;

    // 將 foo[2] 的每個元素加上 foo[1] 的兩倍
    for ( i = 0 ; i < 3 ; ++i ) foo[2][i] += 2 * foo[1][i] ;
    
    cout << "\n> foo[2][i] += 2 * foo[1][i]  ==>  foo[2] = " 
         << foo[2] << endl ;

    return 0 ;
    
}
