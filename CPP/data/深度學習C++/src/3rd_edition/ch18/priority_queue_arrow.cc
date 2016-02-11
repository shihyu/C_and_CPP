#include <iostream>
#include <string>
#include <queue>

using  namespace  std ;

struct  Record {
    string        name ;
    int          score ;
    Record( const string& n , int s ) : name(n) , score(s) {}
};

// 定義 Record 成績的判斷式
bool  operator< ( const Record& a , const Record& b ) {
    return  a.score < b.score ;
}

// 輸出運算子
ostream&  operator<< ( ostream& out , const Record& foo ) {
    return  out << foo.name << " : " << foo.score ;
}

int main() {

    // 使用預設的 less<Record> 為判斷優先次序標準，
    // 分數低的優先次序也小
    priority_queue<Record>  contestant ;

    // 輸入比賽記錄到參賽者優先佇列內
    contestant.push( Record("趙一傷" , 7 ) ) ;  
    contestant.push( Record("錢二敗" , 5 ) ) ;
    contestant.push( Record("孫三毀" , 9 ) ) ;
    contestant.push( Record("李四摧" , 8 ) ) ;
    
    // 列印結果，依次印出
    while ( ! contestant.empty() ) {
        cout << contestant.top() << "   " ;
        contestant.pop() ;
    }
    cout << endl ;
    
    return 0 ;
}
