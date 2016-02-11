#include <iostream>
#include <vector>
#include <cassert>

using  namespace  std ;

// 堆疊類別
template  <class  T> 
class  Stack {
    
  private :

    vector<T>   data  ;  // 元素陣列

  public :

    void pop() ;                               // 從堆疊中取出元素
    void push( const T& item ) ;               // 將元素放入堆疊中
    T    top() const { return  data.back() ; } // 告知最上一個元素
    int  size() const { return data.size() ; } // 告知堆疊元素大小
        
    template <class S> 
    friend  ostream&  operator << ( ostream&  , const Stack<S>& ) ;
    
} ;

// 從堆疊中取出元素
template <class T>
void  Stack<T>::pop() {
    assert( data.size() > 0 ) ;
    data.pop_back() ;
}

// 將元素放入堆疊中
template <class T>
void  Stack<T>::push( const T& item ) { data.push_back(item) ; }
    
// 列印堆疊物件
template <class T>
ostream&  operator << ( ostream& out , const Stack<T>& foo ) {

    out << "> 堆疊共有 " << foo.size() << " 個元素" << endl ;
    out << "  頂端 [ "  ;
    for ( int i = foo.size()-1 ; i >=0 ; --i ) 
        out << foo.data[i] << ' ' ;
    
    return  out << "] 末端" << endl ;

}

int main() {

    Stack<int>  foo ;
    
    // 加入 1 , 2 , 3 , 8 至 堆疊
    foo.push(1) ;  foo.push(2) ;  foo.push(3) ;  foo.push(8) ;
    cout << "> 最頂端元素為 : " << foo.top() << endl ;
    cout << "> 元素個數為   : " << foo.size() << endl << endl ;
    
    // 取出兩個元素後, 加入 9 , 7 , 5 
    foo.pop() ;  foo.pop() ;  foo.push(9) ;  foo.push(7) ;  
    foo.push(5) ;
    cout << foo  ;

    return 0 ;
    
}

   
