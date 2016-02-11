#include <iostream>
#include <assert.h>

using namespace std ;

// 堆疊類別 : 堆疊元素內定個數為 10 個 
template  < class  T , int Stack_Size = 10 >
class  Stack {
    
  private :
    int  count ;             // 堆疊已儲存元素個數
    T    data[Stack_Size] ;  // 元素陣列

  public :
    Stack<T,Stack_Size>() : count(0) {} ;
    
    T     pop() ;                  // 從堆疊中取出元素
    bool  push( const T& item ) ;  // 將元素放入堆疊中
    
    template <class S, int size> 
    friend  ostream&  operator << ( ostream&  , 
                                    const Stack<S,size>& ) ;
    
} ;

// 從堆疊中取出元素
template <class T, int Stack_Size>
T  Stack<T,Stack_Size>::pop() {
    assert( count > 0 ) ;
    return data[--count] ;
}

// 將元素放入堆疊中
template <class T, int Stack_Size>
bool Stack<T,Stack_Size>::push( const T& item ) {
    if ( count >= Stack_Size ) return false ;
    data[count++] = item ;
    return true ;
}
    
// 列印堆疊物件
template <class T, int Stack_Size>
ostream&  operator << ( ostream& out , 
                        const Stack<T,Stack_Size>& foo ) {

    out << "> The stack ( size = " << Stack_Size << " ) has " 
        << foo.count << " items" << endl ;
    out << "  top [ "  ;
    for ( int  i = foo.count-1 ; i >= 0 ; --i ) {
        out << foo.data[i] ;
        if ( i != 0 ) out << " , " ;
    }
    return  out << "  ] bottom" << endl ;

}

main() {

    // 定義可以儲存三個整數的堆疊
    Stack<int,3>  foo ;
    
    foo.push(1) ;   foo.push(2) ;   foo.push(3) ;   foo.push(4) ;
    foo.pop()   ;   foo.push(5) ;   foo.pop()   ;   foo.push(6) ;
    cout << foo << endl ;    

    // 定義可以儲存十個字元的堆疊
    Stack<char>  bar ;

    bar.push('a') ;   bar.push('b') ;   bar.push('c') ;   
    bar.push('d') ;   bar.push('e') ;   bar.pop()     ;   
    bar.push('f') ;
    cout << bar << endl ;    

    // 定義可以儲存十個單精確度浮點數的堆疊
    Stack<float>  fbar ;

    fbar.push(1.1) ;    fbar.push(2.2) ;    fbar.push(3.3) ;    
    fbar.pop()     ;    fbar.push(4.4) ;    fbar.pop()     ;    
    fbar.push(5.5) ;
    cout << fbar << endl ;    

    return 0 ;
    
}

   
