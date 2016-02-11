#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std ;

int main() {

    // 作曲家名單字串
    string   famous_composers = 
       "Vivaldi Handel Bach Haydn Mozart Beethoven Paganini "
       "Schubert Berlioz Weber Mendelssohn Chopin Schumann Liszt "
       "Bramhs Bruch Tchaikovsky Dvorak Sibelius Strawinsky "
       "Shostakovitch" ;
    
    // 複對映容器
    multimap<char,string>  collection ;
    string                 composer ;
    
    istringstream  istring(famous_composers) ;
    
    // 將作曲家一一取出後, 加入複對映容器內
    while( istring >> composer ) 
        collection.insert( make_pair(composer[0],composer) ) ;
    
    typedef  multimap<char,string>::iterator  mmiter ;

    char                 letter ;
    mmiter               iter ;

    pair<mmiter,mmiter>  piter ;
    
    while ( 1 ) {
        cout << "> 輸入作曲家名字的第一個字母 : " ;
        cin >> letter ;

        // 若是小寫字母則改成大寫, 若非大寫字母則重複讀入
        if ( letter >= 'a' && letter <= 'z' ) letter = letter - 'a' + 'A' ;
        if ( letter < 'A' || letter > 'Z' ) break ;

        // 使用字母, 搜尋可能的作曲家名單
        piter = collection.equal_range( letter ) ;

        // 列印結果
        for ( iter = piter.first ; iter != piter.second ; ++iter ) 
            cout << iter->second << "   " ;

        cout << endl ;
    }

    return 0 ;
    
}
