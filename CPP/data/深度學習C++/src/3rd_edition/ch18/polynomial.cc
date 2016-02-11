#include <iostream>
#include <vector>
#include <list>

using namespace std ;

// 多項式的每一項 
template <class T>
struct  Item {
    int     deg ;    // X 的次方數
    T       coeff ;  // X 的係數

    Item( int d = 0 , T c = 1 ) : deg(d) , coeff(c) {}

    // 輸出項的資料
    friend  ostream&  operator<< ( ostream& out , 
                                   const Item<T>& foo ) {
        return  out << ( foo.coeff > 0 ? " + " : " - " ) 
                    << ( foo.coeff > 0 ? foo.coeff : -foo.coeff )
                    << " X^" << foo.deg ;
    }

};

// 多項式判斷式 : 次方數小者優先
template <class T>
struct  small_degree {
    bool  operator() ( const Item<T>& a , const Item<T>& b ) const {
        return  a.deg < b.deg ;
    }
};

// 多項式類別
template <class T>
class  Polynomial {
    
  private :
    
    list< Item<T> >       items ;        // 儲存多項式的每一項
    
  public :

    // 預設建構函式
    Polynomial<T>() {}
    
    // 一般建構函式
    template<class Iter>
    Polynomial<T>( Iter first , Iter last ) 
        : items(first,last) {
        typename  list< Item<T> >::iterator   iter ;

        // 去除零係數的項式
        for ( iter = items.begin() ; iter != items.end() ; 
              ++iter ) {
            if ( iter->coeff == 0 ) {
                // 回傳的迭代器指向下一筆資料
                iter = items.erase(iter) ;  

                // 迭代器指回到上一筆資料
                --iter ;                    
            }
        }

        // 由次方數小者排序
        items.sort( small_degree<T>() ) ;
    }
        
    // 插入一項到多項式內
    void  insert( const Item<T>& item ) {

        // 若係數為零, 則直接跳出
        if ( item.coeff == 0 ) return ;

        // 如果多項式為空多項式 或是 輸入的次方數大於多項式的
        // 最高次方數, 則直接加上末尾
        if ( items.size() == 0 || item.deg > items.back().deg ) {

            items.push_back( item ) ;

        } else {

            // 定義一串列迭代器物件
            typename  list< Item<T> >::iterator   iter ;

            // 找出是否已有同次方數的 X 項, 若有則直接其值加入其內
            for ( iter = items.begin() ; iter != items.end() ; 
                  ++iter ) {

                if ( item.deg < (*iter).deg ) {
                    items.insert( iter , item ) ;
                    return ;
                } else if ( item.deg == (*iter).deg ) {
                    iter->coeff += item.coeff ;
                    // 如果係數最後為 0, 則去除此項
                    if ( iter->coeff == 0 ) items.erase( iter ) ;
                    return ;
                }

            }

        }
    }

    // 列印多項式 
    friend  ostream& operator<< ( ostream& out , 
                                  const Polynomial<T>& foo ) {

        typename  list< Item<T> >::const_iterator   iter ;
        for ( iter = foo.items.begin() ; 
              iter != foo.items.end() ;  ++iter )  out << *iter ;
        return out ;

    }

};

int main() {
    
    Polynomial<int>  foo  ;
    
    // 交錯將各項存入多項式,  foo = X - 2 X^1 + 3 X^2 - 4 X^3
    for ( int i = 3 ; i >= 0 ; --i ) {  
        if ( i % 2 == 0 ) 
            foo.insert( Item<int>(i,i+1) ) ;
        else
            foo.insert( Item<int>(i,-(i+1)) ) ;

    }

    // foo = + 1 X^0 - 2 X^1 + 3 X^2 - 4 X^3
    cout << "foo = " << foo << endl ;

    // 加入  4 X^2 + 4 X^3 + 4 X^4 + 4 X^5
    for ( int i = 2 ; i <= 5 ; ++i ) foo.insert( Item<int>(i,4) ) ;
    
    // foo =  + 1 X^0 - 2 X^1 + 7 X^2 + 4 X^4 + 4 X^5
    cout << "foo = " << foo << endl ;


    // 使用向量陣列儲存多項式的一些項式
    vector< Item<int> >   items ;

    for ( int i = 10 ; i >= 0 ; i -= 2 )
       items.push_back( Item<int>(i,i) ) ;

    // 將向量陣列的資料存入多項式類別
    Polynomial<int>  bar(items.begin(),items.end()) ;
    
    cout << "bar = " << bar << endl ;

    return 0 ;
    
}

