#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std ;

class  Random_Shuffle {
  private :

    int        counter ;   // 計數
    int        size  ;     // 元素個數
    int*       items ;     // 元素陣列

    // 對調元素
    void  swap( int& a , int& b ) const {
        int c = a ;
        a = b ;
        b = c ;
    }
    
    // 重新排列 items 陣列元素
    void  random_shuffle() {
        int i , j ;
        for ( i = size-1 ; i > 0 ; --i ) {
            j = rand()%(i+1) ;
            if ( i != j ) swap(items[i],items[j]) ;
        }
    }

  public :

    // 建構函式
    Random_Shuffle( int a , int b ) 
        : counter(0) , size(b-a+1) {
        
        items = new int[size] ;
        
        int  i , c = a ;
        for ( i = 0 ; i < size ; ++i , ++c ) items[i] = c ;

        srand( static_cast<unsigned>(time(NULL)) ) ;

        // 重新排列 items 陣列
        random_shuffle() ;
    }

    // 複製建構函式
    Random_Shuffle( const Random_Shuffle& foo ) {
        counter = foo.counter ;
        size = foo.size ;
        items = new int[size] ;

        for ( int i = 0 ; i < size ; ++i ) items[i] = foo.items[i] ;
    }
    
    // 指定運算子
    void  operator= ( const Random_Shuffle& foo ) {

        counter = foo.counter ;

        if ( size != foo.size ) {
            if ( size > 0 ) delete [] items ;
            size = foo.size ;
            items = new int[size] ;
        }
        for ( int i = 0 ; i < size ; ++i ) items[i] = foo.items[i] ;
        
    }

    // 取得一個元素
    int  get() {

        if ( counter == size ) {
            random_shuffle() ;
            counter = 0 ;
        }

        return items[counter++] ;
    }

    // 陣列長度
    int  len() const { return  size ; }
    
    // 解構函式
    ~Random_Shuffle() { delete [] items ; }
    
};


int main() {

    int  i ;

    // 1 到 5 
    Random_Shuffle  a(1,5) ;       
    for ( i = 1 ; i <= 15 ; ++i ) {
        cout << a.get() ;
        if ( i%a.len()==0 ) cout << " " ;
    }
    cout << endl ;

    // 7 到 9
    Random_Shuffle  b(7,9) ;      
    for ( i = 1 ; i <= 15 ; ++i ) {
        cout << b.get() ;
        if ( i%b.len()==0 ) cout << " " ;
    }
    cout << endl ;

    // 複製 a 給 b
    b = a ;
    for ( i = 1 ; i <= 15 ; ++i ) {
        cout << b.get() ;
        if ( i%b.len()==0 ) cout << " " ;
    }
    cout << endl ;
    
    return 0 ;
    
}
