#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>

using namespace std ;

template <class T>
class Vec {
    
  private :
    
    vector<T>  dat ;     // 用向量陣列儲存向量的元素
    
  public :

    Vec() {}
    
    Vec( const vector<T>& foo ) : dat(foo) {}

    // 向量元素個數
    int size() const { return dat.size() ; }

    // 下標運算子
    T&          operator[] ( int i )       {  return dat[i] ; }
    const  T&   operator[] ( int i ) const {  return dat[i] ; }

    // 定義 += 運算子
    Vec&  operator-= ( const Vec& a ) {
        assert( dat.size() == a.size() ) ;
        for ( int i = 0 ; i < dat.size() ; ++i ) dat[i] -= a.dat[i] ;
        return  *this ;
    }

    // 定義 Vec 專用的輸入運算子
    template <class S>
    friend  istream&  operator>> ( istream& in , Vec<S>& foo ) {
        string  line ;
        getline( in , line ) ;
        istringstream  istr(line) ;
        S  tmp ;
        while ( istr >> tmp ) foo.dat.push_back(tmp) ;
        return  in ;
    }

};

// 定義 Vec 專用的輸出運算子
template <class S>
ostream&  operator<< ( ostream& out , const Vec<S>& foo ) {
    out << "( " ;
    for ( int i = 0 ; i < foo.size() ; ++i ) out << foo[i] << ' ' ;
    return  out << ")" ;
}

// 計算兩向量的加法
template <class T>
Vec<T>  operator+ ( const Vec<T>& a , const Vec<T>& b ) {
    assert( a.size() == b.size() ) ;

    // 定義一向量陣列  後將兩向量物件的元素合成到向量陣列中
    vector<T>  foo(a.size()) ;
    for ( int i = 0 ; i < foo.size() ; ++i ) foo[i] = a[i] + b[i] ;
    return  Vec<T>(foo) ;
}

// 計算兩向量的內積和
template <class T>
T  operator* ( const Vec<T>& a , const Vec<T>& b ) {
    assert( a.size() == b.size() ) ;
    T  sum = static_cast<T>(0.) ;
    for ( int i = 0 ; i < a.size() ; ++i ) sum += a[i] * b[i] ;
    return  sum ;
}
        
int  main() {
    
    Vec<int>  a , b ;
    cout << "> 分別輸入兩個向量 (元素個數相同) : \n" ;
    cout << "a = " ;    cin  >> a ;
    cout << "b = " ;    cin  >> b ;
    
    cout << "a + b  => " << a + b  << endl ;
    cout << "a * b  => " << a * b  << endl ;
    cout << "a -= b => " << (a -= b) << endl ;

    return 0 ;
    
}

        
    
