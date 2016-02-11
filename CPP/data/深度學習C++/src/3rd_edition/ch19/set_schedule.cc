#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

using namespace std ;

typedef  string  Course  ;
typedef  int     Section ;

enum  Weekday  { Sun , Mon , Tue , Wed , Thu , Fri , Sat };

// 課程結構
struct  Schedule { 

    Course    name ;  // 課程名稱
    Weekday   day  ;  // 授課日期
    Section   sct  ;  // 授課時間

    // 兩個建構函式
    Schedule(){} ;
    Schedule( Course n , Weekday d , Section s ) 
        : name(n) , day(d) , sct(s) {}
};


// 設定小於比較函式, 以節數小者的資料較小, 若相等, 則授課日小者較小
bool  operator< ( const Schedule& a , const Schedule& b ) {
    return ( a.sct == b.sct ? a.day < b.day : a.sct < b.sct ) ;
}


class  Course_Schedule{

  private :

    // 依 課程 Schedule 的順序, 儲存課程資料
    set<Schedule>  courses ;   

  public :

    // 建構函式, 讀取資料
    Course_Schedule( char* datafile ) {

        ifstream        infile(datafile) ;
        string          line ;
        istringstream   strline(line) ;

        Course   cname ;
        Weekday  wday ;
        Section  sct ;
        string   day ;
        char     colon ;
        
        // 讀入一行資料, 將每一授課時間存入 courses 優先序列
        while ( getline( infile , line ) ) {

            strline.str(line) ;
            strline >> cname ;

            // 讀入課程的授課日期
            while ( strline >> day ) {

                // 設定授課日變數
                if ( day == "Mon" )       wday = Mon ;
                else if ( day == "Tue" )  wday = Tue ;
                else if ( day == "Wed" )  wday = Wed ;
                else if ( day == "Thu" )  wday = Thu ;
                else if ( day == "Fri" )  wday = Fri ;
                else if ( day == "Sat" )  wday = Sat ;
                
                // 讀取冒號
                strline >> colon ;

                // 讀入課程的授課時間, 直到發生讀入錯誤為止
                while ( strline >> sct ) 
                    courses.insert( Schedule(cname,wday,sct) ) ;

                // 清除讀入錯誤旗幟
                strline.clear() ;
            }

            strline.clear() ;

        }

    }

    // 列印課程表
    void  print_html_schedule() const {

        char*  weekday[] = { "星期日" , "星期一" , "星期二" , 
                             "星期三" , "星期四" , "星期五" , 
                             "星期六" };

        int   s , d ;


        // 產生 HTML 開始, 網頁名稱, 及網頁的主體部份等標記
        cout << "<html><head><title>課程表</title></head>\n" 
             << "<body>" ;
        
        // 產生課程表表格第一列標頭
        cout << "<table border=1 cellpadding=3>\n" 
             << "<tr><th bgcolor=white width=5%><br></th>\n" ;

        for ( d = 1 ; d <= 5 ; ++d ) 
            cout << "<th width=16% bgcolor=cyan>" 
                 << weekday[d] << "</th>\n" ;
                 

        cout << "</tr>" ;
        
        // 取出最優先的課程
        set<Schedule>::const_iterator  iter = courses.begin() ;

        // 列印課表, 採用橫排節數, 直排日期
        for ( s = 1 ; s <= 8 ; ++s ) {

            // 開始新的一列, 同時節數欄位用淺藍色背景, 置中對齊顯示
            cout << "<tr><td bgcolor=cyan align=center>" 
                 << s << "</td>\n";

            for ( d = 1 ; d <= 5 ; ++d ) {

                // 課程名稱的每一欄用白色背景, 置中對齊顯示
                cout << "<td bgcolor=white align=center>" ;

                // 如果此日此節有課, 則以紅色字列印後, 
                // 迭代器隨即指向下一個元素
                if ( iter->day == d && iter->sct == s ) {
                    cout << "<font color=red>" 
                         << iter->name.c_str() << "</font>" ;
                    if ( iter != courses.end() ) ++iter ;
                }
                cout << "<br></td>\n" ;

            }

            // 終結一列
            cout << "</tr>\n" ;
        }

        // 加上 HTML 末尾標記
        cout << "</table></body></html>" ;
        
    }
    
};

// 主函式
int  main() {

    Course_Schedule  courses("class.db") ;

    // 列印 HTML 課表
    courses.print_html_schedule() ;
    
    return 0 ;
    
}

