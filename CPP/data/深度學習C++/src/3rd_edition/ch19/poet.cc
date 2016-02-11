#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std ;

int main() {

    string   foo[4] = { "李白    夜思 怨情"  ,  "王維    送別 相思" , 
                        "杜牧    清明"       ,  "杜甫    八陣圖"   } ;
    
    typedef  string  POET ;   // 詩人
    typedef  string  POEM ;   // 詩名
    
    multimap<POET,POEM>  collection ;
    string               poet , poem ;
    istringstream  istring(poem) ;    
    
    for ( int  i = 0 ; i < 4 ; ++i ) { 
        // 將每個字串送入字串資料流物件, 取出詩人名字
        istring.str( foo[i] ) ;
        istring >> poet ;
        
        // 依次將詩取出, 產生成對物件, 後插入複對映物件中
        while ( istring >> poem ) collection.insert( make_pair(poet,poem) ) ;

        // 去除 failbit 
        istring.clear() ;
        
    }

    // 依次列印整個複對映物件    
    multimap< POET , POEM >::iterator  iter1 ;
    for ( iter1 = collection.begin() ; iter1 != collection.end() ; ++iter1 )
        cout << iter1->first << " : " << iter1->second << endl ;
    cout << endl ;
    
    // 將複對映容器資料插入到對映物件中, 但相同的索引不作插入動作
    map<POET,POEM>  single ;
    single.insert( collection.begin() , collection.end() ) ;
    
    // 依次列印整個對映物件    
    map< string , string >::iterator  iter2 ;
    for ( iter2 = single.begin() ; iter2 != single.end() ; ++iter2 )
        cout << iter2->first << " : " << iter2->second << endl ;

    return 0 ;
    
}
