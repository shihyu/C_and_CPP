#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

using namespace std ;

typedef  string  Poet ;

// 定義作品結構
struct  Poem {
    Poet    poet ;
    string  name ;
    string  content ;
};

// 針對 Poem 定義輸入運算子
istream&  operator>> ( istream& in , Poem& poem ) {
    string  content ;
    in >> poem.poet >> poem.name >> poem.content ;
    while ( in >> content ) poem.content += "  " + content ;
    return in ;
}

// 針對 Poem 定義輸出運算子
ostream&  operator<< ( ostream& out , const Poem& poem ) {
    return  out << poem.poet 
                << setw(poem.content.size()-poem.poet.size()-
                        poem.name.size()) << " " 
                << poem.name << "\n" << poem.content  ;
}

// 資料庫類別
class  Poem_db {

  private :
    
    // 根據詩人儲存其作品
    multimap<Poet,Poem>  poem_db ;

    // 讀取資料檔
    void  read_datafile ( char* datafile ) {
    
        // 開啟檔案
        ifstream  infile(datafile) ;
        string    line ;

        Poem            poem ;
        istringstream   data_line ;
    
        // 每次讀取一行後, 轉成 Poem 物件後再差入 poem_db 
        // 複對映容器內
        while ( getline( infile , line ) ) {
            data_line.str(line) ;
            data_line >> poem ;
            poem_db.insert( make_pair( poem.poet , poem ) ) ;
            data_line.clear() ;
        }
        
    }
    
  public :

    typedef  multimap<Poet,Poem>::const_iterator   Pciter ;

    // 建構函式 : 讀取資料檔
    Poem_db( char* datafile ) {  read_datafile( datafile ) ;   }

    // 搜尋詩人在資料檔中的所有作品
    vector<Poem>  find( const Poet& poet ) const ;
    
};

// 搜尋詩人在資料檔中的所有作品
vector<Poem>  Poem_db::find( const Poet&  poet ) const {
    
    Pciter               iter ;
    pair<Pciter,Pciter>  piter ;

    // 搜尋詩人
    piter = poem_db.equal_range(poet) ;

    vector<Poem>   poems ;
    for ( iter = piter.first ; iter != piter.second ; ++iter ) {
        poems.push_back(iter->second) ;
    }
    
    return  poems ;
    
}

// 主函式
int  main() {

    Poem_db       poem_database("poem.db") ;
    
    int           i     ;
    Poet          poet  ;
    vector<Poem>  poems ;
    
    while ( 1 ) {
        cout << "> 輸入詩人名字 : " ;
        cin >> poet ;
        poems = poem_database.find( poet ) ;
        for ( i = 0 ; i < poems.size() ; ++i ) {
            cout << "[" << i+1 << "]\n" 
                 << poems[i] << "\n\n" ;
        }
        if ( poems.empty() ) {
            cout << "> 唐詩資料庫中查無此詩人\n" ;
            break ;
        }
    }

    return 0 ;
    
}

