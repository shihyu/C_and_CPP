#include <iostream>

using namespace std ;

// 集合元素儲存狀態
enum  Status  { empty , occupied };

// 集合類別
class  Set {

  private :

    // Default_Size : 預設的集合最小可儲存元素的個數 
    // Inc_Size     : 每次增加的元素個數
    enum { Default_Size = 10 , Inc_Size = 20 } ;
    
    int     *element       ;    // 元素
    Status  *status        ;    // 元素儲存狀態
    int     element_no     ;    // 已儲存的元素個數
    int     max_element_no ;    // 可儲存的元素個數

  public :
    
    // 預設建構函式
    Set() : element_no(0) , max_element_no(Default_Size) {
        element = new int[Default_Size] ;
        status  = new Status[Default_Size] ;
        for ( int i = 0 ; i < Default_Size ; ++i ) 
            status[i] = empty ;
    }

    // 解構函式
    ~Set() {  delete [] element ;  delete [] status  ;   }
    
    // 複製建構函式
    Set( const Set& set ) ;
    
    // 指定運算子 : 這裡暫先設為不回傳任何資料
    void  operator=( const Set& set ) ;

    // 加入元素
    void  insert_element( int data ) ;
    
    // 刪除元素
    int   delete_element( int data ) ;
    
    // 列印元素
    void  print_set() const ;
    
};

int  main() {
    
    // 使用內定建構函式
    Set  set1 ;

    // 儲存 20 個個位數元素
    for( int i = 0 ; i < 20 ; ++i ) set1.insert_element( i%10 ) ;
    set1.print_set() ;

    // 測試複製建構函式
    Set  set2(set1) ;
    set2.print_set() ;

    // 增減集合元素
    set2.insert_element(5) ;  set2.insert_element(9) ;
    set2.delete_element(3) ;  set2.delete_element(0) ;
    set2.print_set() ;

    // 測試指定運算子
    set1 = set2 ;
    set1.print_set() ;

    return 0 ;
    
}

// 增加元素
void  Set::insert_element ( int data ) {

    int  i ;

    // 如果現有的元素個數已經滿了, 則須另尋空間儲存
    if ( element_no == max_element_no ) {

        int    *tmp_element = new    int[max_element_no+Inc_Size] ;
        Status *tmp_status  = new Status[max_element_no+Inc_Size] ;
        
        // 複製現有元素到新的記憶空間
        for ( i = 0 ; i < max_element_no ; ++i ) {
            tmp_element[i] = element[i] ;
            tmp_status[i]  = status[i] ;
        }
        
        // 儲存新元素
        tmp_element[max_element_no] = data ;
        tmp_status[max_element_no]  = occupied ;

        for ( i = 1 ; i < Inc_Size ; ++i ) {
            tmp_status[max_element_no+i] = empty ;
        }
        
        // 釋放舊記憶空間
        delete [] element ;    delete [] status  ;
        
        element = tmp_element ;
        status  = tmp_status  ;
        
        max_element_no += Inc_Size ;
        ++element_no ;
        
    } else {

        // 原有空間已夠用, 直接增加一個元素
        for ( i = 0 ; i < max_element_no ; ++i ) {
            if ( status[i] == empty ) {
                element[i] = data ;
                status[i]  = occupied ;
                ++element_no ;
                return ;
            }
        }
        
    }
    
}

// 刪除元素
int  Set::delete_element( int data ) {

    // 定義變數表示刪除元素的個數
    int  no_element_deleted = 0 ;

    for ( int i = 0 ; i < max_element_no ; ++i ) {

        // 尋找到元素後刪除
        if ( status[i] == occupied  &&  element[i] == data ) {
            status[i] = empty ;
            --element_no ;
            ++no_element_deleted ;
        }

    }
    return  no_element_deleted ;
}

// 列印元素
void  Set::print_set( void ) const {

    cout << "集合有 " << element_no << " 元素 : " ;

    for ( int i = 0 ; i < max_element_no ; ++i ) 
        if ( status[i] == occupied ) cout << element[i] << ' ' ;

    cout << endl ;

}

// 複製建構函式
Set::Set( const Set& set ) {

    element_no     = set.element_no ;
    max_element_no = set.max_element_no ;
        
    element = new int[max_element_no] ;
    status  = new Status[max_element_no] ;
        
    for ( int i = 0 ; i < max_element_no ; ++i ) {
        element[i] = set.element[i] ;
        status[i]  = set.status[i]  ;
    }

}

// 指定運算子
void  Set::operator=( const Set& set ) {

    // 如果所欲複製的集合類別的元素較現有的空間多, 
    // 則須要重新分配空間, 否則利用現有的空間即可
    if( set.element_no > max_element_no ) {
        
        element_no     = set.element_no ;
        max_element_no = set.max_element_no ;
        
        int     *tmp_element = new int[max_element_no] ;
        Status  *tmp_status  = new Status[max_element_no] ;
        
        for ( int i = 0 ; i < max_element_no ; ++i ) {
            tmp_element[i] = set.element[i] ;
            tmp_status[i]  = set.status[i]  ;
        }

        // 釋放現有的記憶空間
        delete [] element ;        delete [] status ;

        // 使用新記憶空間
        element = tmp_element ;
        status  = tmp_status ;

    } else {

        int i , c = 0 ;
        element_no  = set.element_no ;

        // 重新分配元素
        for ( i = 0 ; i < set.max_element_no ; ++i ) {
            if ( set.status[i] == occupied ) {
                element[c] = set.element[i] ;
                status[c]  = occupied ;
                ++c ;
            }
        }

        for ( i = c ; i < max_element_no ; ++i )
            status[i] = empty ;

    }

}
