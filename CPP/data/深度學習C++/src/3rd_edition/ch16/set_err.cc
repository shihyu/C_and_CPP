#include <iostream>

using  namespace  std ;

// 定義處理集合執行錯誤類別
class  Set_Error {

  public :

    // 設定兩個集合的錯誤種類的形態
    enum  error_type  { under_set , over_set } ;  

  private:

    // 錯誤種類
    error_type  kind ;
 
  public :

    // 建構函式
    Set_Error(error_type type) : kind(type) {} ;

    // 重列印錯誤訊習
    friend  ostream& operator << ( ostream& out , 
                                   const Set_Error& err ) ;

};


// 定義模板集合類別
template < class T , int Set_Size = 5 >
class Set {

  private :

    int    count              ;  // 已有的集合元素個數
    T      data[Set_Size]     ;  // 儲存元素的陣列
    bool   occupied[Set_Size] ;  // 是否陣列的某個位置已儲存元素

  public:

    // 內定建構函式
    Set() throw() : count(0) {
        for( int i = 0 ; i < Set_Size ; ++i ) occupied[i] = false ;
    }

    // 移除元素
    bool  remove( const T& item ) throw(Set_Error) ;

    // 加入元素
    bool  insert( const T& item ) throw(Set_Error) ;

    // 列印集合所有的元素
    template <class S, int size>
    friend  ostream&  operator << 
          ( ostream& out , const Set<S,size>& foo ) throw() ;

} ;

// 針對 Set_Error 類別重新定義輸出運算子
ostream&  operator << ( ostream& out , const Set_Error& err ) {
    
    if ( err.kind == Set_Error::under_set ) {
        out << "> 集合執行錯誤 : 無法由一空集合中移除元素" ;
    } else if ( err.kind == Set_Error::over_set ) {
        out << "> 集合執行錯誤 : 集合空間已滿, 無法加入元素" ;
    }
    return out ;
      
}

// 由集合內刪除元素
template <class T , int Set_Size>
bool Set<T,Set_Size>::remove(const T& item) throw(Set_Error) {

    // 集合已空, 擲出錯誤物件
    if ( count == 0 ) throw  Set_Error( Set_Error::under_set ) ;

    for ( int i = 0 ; i < Set_Size ; ++i ) {
        if ( occupied[i] && data[i] == item ) {
            occupied[i] = false ;
            --count ;
            return true ;
        }
    }

    // 如果沒找到元素, 則回傳假值
    return  false ;
    
}

// 加入元素到集合內
template <class T, int Set_Size>
bool Set<T,Set_Size>::insert( const T& item ) throw(Set_Error) {

    // 集合已滿, 擲出錯誤物件
    if ( count == Set_Size ) 
        throw Set_Error( Set_Error::over_set ) ;

    for ( int i = 0 ; i < Set_Size ; ++i ) {
        if ( ! occupied[i] ) {
            occupied[i] = true ;
            data[i] = item ;
            ++count ;
            return true ;
        }
    }

}

// 列印集合 
template <class T, int Set_Size>
ostream& operator << ( ostream& out , 
                       const Set<T,Set_Size>& foo ) throw() {
 
    out << "> 集合 [ 可儲存元素個數 = " << Set_Size 
        << " ] 共有 " << foo.count << " 個元素\n" << " ( " ;

    if ( foo.count != 0 ) {

        bool first_item = true ;
        for ( int i = 0 ; i < Set_Size ; ++i ) {

            if ( ! foo.occupied[i] ) continue ;

            if ( first_item ) {
                out << foo.data[i] ;
                first_item = false ;
            } else 
                out << " , " << foo.data[i] ;

        }

    } 

    return  out << " )\n" ;

}

int main() {

    Set<int,20>  foo1 , foo2 ;
    Set<double>  foo3 , foo4 ;

    // 測試 整數集合 foo1, 可以儲存有 20 個元素
    try {
        foo1.insert(6) ; foo1.insert(8) ; foo1.insert(7) ;
        foo1.remove(8) ; foo1.remove(6) ; foo1.remove(9) ;
        foo1.remove(7) ; foo1.remove(5) ;

        cout << "[正確] foo1 : \n" << foo1 << endl ;
    }

    catch ( const Set_Error& error ) {
        cout << "[錯誤] foo1 : \n" << error << "\n" << foo1 << endl ;
    }

    // 測試 整數集合 foo1, 可以儲存有 20 個元素
    try {
        foo2.insert(1) ; foo2.insert(2) ; foo2.insert(3) ; 
        foo2.insert(9) ; foo2.remove(4) ; foo2.insert(5) ; 
        foo2.remove(3) ; foo2.insert(6) ; foo2.remove(4) ;

        cout << "[正確] foo2 : \n" << foo2<< endl ;
    }

    catch ( const Set_Error& error ) {
        cout << "[錯誤] foo2 : \n" << error << "\n" << foo2 << endl ;
    }

    // 測試 雙精度浮點數集合 foo3, 可以儲存 5 個元素
    try {
        foo3.insert(1.1) ; foo3.insert(2.2) ; foo3.insert(3.3) ; 
        foo3.insert(4.4) ; foo3.insert(5.5) ; foo3.insert(6.6) ; 
        foo3.insert(7.7) ; foo3.insert(8.8) ; foo3.insert(9.9) ;

        cout << "[正確] foo3 : \n" << foo3 << endl ;
    }

    catch ( const Set_Error& error ) {
        cout << "[錯誤] foo3 : \n" << error << "\n" << foo3 << endl ;
    }

    // 測試 雙精度浮點數集合 foo4, 可以儲存 5 個元素
    try {
        foo4.remove(1.9) ; 
        foo4.insert(1.1) ; foo4.insert(2.2) ; foo4.insert(3.3) ; 
        foo4.insert(4.4) ; foo4.insert(5.5) ; 

        cout << "[正確] foo4 : \n" << foo4 << endl ;
    }

    catch( const Set_Error& error ) {
        cout << "[錯誤] foo4 : \n" << error << "\n" << foo4 << endl ;
    }

    return 0 ;
    
}
