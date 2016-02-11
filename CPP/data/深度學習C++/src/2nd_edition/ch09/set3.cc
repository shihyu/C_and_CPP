#include <iostream>

using namespace std ;

// 定義集合最多能儲存多少元素
const  int  SIZE = 10 ;

// 設定是否集合元素陣列的儲存狀態
enum   Status  { empty , occupied } ;

// 定義集合組織資料型別
class  Set {

  private :
    int     element[SIZE] ;    // 儲存集合元素
    Status  status[SIZE]  ;    // 每個集合位置的狀態
    int     element_no    ;    // 集合元素的個數

  public :

    // 內定建構函式
    Set(void) {
        for ( int i = 0 ; i < SIZE ; ++i ) status[i] = empty ;
        element_no = 0 ;
    }

    // 第二個建構函式, 產生 no 個同樣的元素 data
    Set( int no , int data ) ;
            
    // 加入元素至集合
    bool  insert_element( int data ) ;
    
    // 刪除集合元素
    int  delete_element( int data ) ;

    // 列印集合
    void  print_set( void ) ;
    
} ;


// 主函式
int  main() {
    
    // 定義集合物件
    Set   foo(3,2) ;
    
    cout << "foo : " ;
    foo.print_set()  ;
    
    // foo 加入元素
    foo.insert_element(3) ;  foo.insert_element(5) ;  
    foo.insert_element(1) ;  foo.insert_element(5) ;
    foo.insert_element(7) ;  foo.insert_element(1) ;  
    cout << "foo : " ;
    foo.print_set()  ;

    // 使用自動產生的複製建構成員函式複製物件
    Set  bar = foo   ;     
    cout << "bar : " ;
    bar.print_set()  ;

    // 刪除元素
    foo.delete_element(1) ;  foo.delete_element(3) ;

    // 使用自動產生的指定運算子成員函式複製物件
    bar = foo ;            
    cout << "bar : " ;
    bar.print_set()  ;

    return 0 ;
    
}

// 第二個建構函式, 產生 no 個同樣的元素 data
Set::Set( int no , int data ) {
    for ( int i = 0 ; i < SIZE ; ++i ) {
        if ( i < no ) {
            element[i] = data ;                
            status[i] = occupied ;
        } else 
            status[i] = empty ;
    }
    element_no = no ;
}

// 加入元素至集合
bool  Set::insert_element( int data ) { 

    // 若集合已滿了, 則禁止加入任何元素
    if ( element_no == SIZE ) return false ;

    // 尋找第一個空著的元素
    for ( int i = 0 ; i < SIZE ; ++i ) {
        if ( status[i] == empty ) {
            element[i] = data ;
            status[i] = occupied ;
            ++element_no ;
            return  true ;
        }
    }
}

// 刪除集合元素
int  Set::delete_element( int data ) {

    // 定義變數表示是否有元素被去除
    int  no_element_deleted = 0 ;

    for ( int i = 0 ; i < SIZE ; ++i ) {
        // 找到集合元素, 同時其值與去除的元素相同
        if ( status[i] == occupied  &&  element[i] == data ) {
            status[i] = empty ;
            --element_no ;
            ++no_element_deleted ;
        }
    }
    return  no_element_deleted ;
}

// 列印集合
void  Set::print_set( void ) {

    cout << "集合有 " << element_no << " 元素 : " ;
    for ( int i = 0 ; i < SIZE ; ++i ) {
        if ( status[i] == occupied )
            cout << element[i] << ' ' ;
    }
    cout << endl ;
}
