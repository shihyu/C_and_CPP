#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

using  namespace  std ;

typedef  string  Poet    ;   // 詩人
typedef  string  Name    ;   // 詩的名稱
typedef  string  Content ;   // 詩的內容

// 詩的資料結構
struct  Poem {
    Poet     poet ;
    Name     name ;
    Content  content ;
};

// 覆載 Poem 輸入運算子
istream&  operator>> ( istream& in , Poem& poem ) {
    string  content ;
    in >> poem.poet >> poem.name >> poem.content ;
    while ( in >> content ) poem.content += "  " + content ;
    return in ;
}

// 覆載 Poem 輸出運算子
ostream&  operator<< ( ostream& out , const Poem& poem ) {
    return  out << poem.poet 
                << setw(poem.content.size()-poem.poet.size()-
                        poem.name.size())
                << " "
                << poem.name << "\n" << poem.content  ;
}

// 唐詩類別
class  Tang_Poem {

  private :

    vector<Poem>   five  ;   // 五言絕句
    vector<Poem>   seven ;   // 七言絕句

  public :

    // 建構函式 : 分別讀入五言與七言絕句資料檔
    Tang_Poem( const char* poem5 , const char* poem7 ) {

        ifstream  infile1(poem5) , infile2(poem7) ;
        string    line ;

        Poem            poem ;
        istringstream   poem_entry ;
    
        // 讀入五言絕句資料檔
        while ( getline( infile1 , line ) ) {
            poem_entry.str(line) ;
            poem_entry >> poem ;
            five.push_back( poem ) ;
            poem_entry.clear() ;
        }

        // 讀入七言絕句資料檔
        while ( getline( infile2 , line ) ) {
            poem_entry.str(line) ;
            poem_entry >> poem ;
            seven.push_back( poem ) ;
            poem_entry.clear() ;
        }
   
    }
    
    // 找尋詩人在資料庫中所有的詩後回傳
    vector<Poem>  search_poet( const Poet& poet ) const {

        int i ;
        vector<Poem>  poems ;
        
        for ( i = 0 ; i < five.size() ; ++i ) 
            if ( five[i].poet == poet ) poems.push_back(five[i]) ;

        for ( i = 0 ; i < seven.size() ; ++i ) 
            if ( seven[i].poet == poet ) poems.push_back(seven[i]);

        return poems ;
    }
    
};


int  main() {
    
    // 唐詩資料庫物件
    Tang_Poem  poem_db( "five_poem.db" , "seven_poem.db" ) ;
    
    Poet          poet  ;   // 詩人
    vector<Poem>  poems ;   // 詩

    int i ;

    // 以 Ctrl-c 鍵跳離迴圈
    while ( 1 ) {
        cout << "> 輸入詩人名字 : " ;
        cin >> poet ;

        // 找尋詩人在唐詩資料庫內中的所有詩
        poems = poem_db.search_poet( poet ) ;

        for ( i = 0 ; i < poems.size() ; ++i ) 
            cout << "\n" << poems[i] << "\n" ;

        cout << endl ;
        
    }

    return 0 ;
    
}
