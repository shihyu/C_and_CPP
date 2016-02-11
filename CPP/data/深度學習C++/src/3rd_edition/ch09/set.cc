#include <iostream>

using namespace std ;

// 定義集合最多能儲存多少元素
const  int  SIZE = 10 ;

// 設定是否集合元素陣列的儲存狀態
enum   Status  { empty , occupied } ;

// 定義集合組織資料型別
struct  Set {
    int     element[SIZE] ;    // 儲存集合元素
    Status  status[SIZE]  ;    // 每個集合位置的狀態
    int     element_no    ;    // 集合元素的個數
} ;

// 集合初值設定
void  set_initialization( Set&  set ) ;

// 加入元素至集合
bool  insert_element( Set& set , int data ) ;

// 刪除集合元素
int  delete_element( Set& set , int data ) ;

// 列印集合
void  print_set( const Set& set ) ;

// 主函式
int  main() {
    
    // 定義集合變數
    Set   myset ;  
    
    // 設定集合變數初值
    set_initialization( myset ) ;  

    // 加入元素
    insert_element( myset , 3 ) ; insert_element( myset , 5 ) ;
    insert_element( myset , 1 ) ; insert_element( myset , 4 ) ;
    insert_element( myset , 1 ) ; insert_element( myset , 7 ) ;
    insert_element( myset , 1 ) ; insert_element( myset , 5 ) ;
    print_set( myset ) ;

    // 刪除元素
    delete_element( myset , 1 ) ;  delete_element( myset , 3 ) ;
    print_set( myset ) ;

    return 0 ;
}


// 集合初值設定
void  set_initialization( Set&  set ) {
    for ( int i = 0 ; i < SIZE ; ++i ) set.status[i] = empty ;
    set.element_no = 0 ;
}

// 加入元素至集合
bool  insert_element( Set& set , int data ) { 

    // 若集合已滿了, 則禁止加入任何元素
    if ( set.element_no == SIZE ) return false ;

    // 尋找第一個空著的元素
    for ( int i = 0 ; i < SIZE ; ++i ) {
        if ( set.status[i] == empty ) {
            set.element[i] = data ;
            set.status[i] = occupied ;
            ++set.element_no ;
            return  true ;
        }
    }
}

// 刪除集合元素
int  delete_element( Set& set , int data ) {

    // 定義變數表示是否有元素被去除
    int  no_element_deleted = 0 ;

    for ( int i = 0 ; i < SIZE ; ++i ) {
        // 找到集合元素, 同時其值與去除的元素相同
        if ( set.status[i]  == occupied  &&  
             set.element[i] == data ) {
            set.status[i] = empty ;
            --set.element_no ;
            ++no_element_deleted ;
        }
    }
    return  no_element_deleted ;
}

// 列印集合
void  print_set( const Set& set ) {

    cout << "集合有 " << set.element_no << " 元素 : " ;
    for ( int i = 0 ; i < SIZE ; ++i ) {
        if ( set.status[i] == occupied )
            cout << set.element[i] << ' ' ;
    }
    cout << endl ;

}
