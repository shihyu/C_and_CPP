#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

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


// 設定 Schedule 結構的順序, 節數小的優先, 若相等, 則授課日小的優先
bool  operator< ( const Schedule& a , const Schedule& b ) {
    return ( a.sct == b.sct ? b.day < a.day : b.sct < a.sct ) ;
}


class  Course_Schedule{

  private :

    // 依 課程 Schedule 的順序, 儲存課程資料
    priority_queue<Schedule>  courses ;   

  public :

    // 建構函式, 讀取資料
    Course_Schedule( char* datafile ) {

        ifstream        infile(datafile) ;
        string          line ;
        istringstream   strline ;

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
                    courses.push( Schedule(cname,wday,sct) ) ;

                // 清除讀入錯誤旗幟
                strline.clear() ;
            }

            // 清除讀入錯誤旗幟
            strline.clear() ;

        }

    }

    // 列印課程表
    void  print_schedule() const {

        char*  weekday[] = { "Sun" , "Mon" , "Tue" , "Wed" , "Thu" , 
                             "Fri" , "Sat" };

        priority_queue<Schedule>  course = courses ;
        Schedule  foo ;
        int       i , s , d ;

        // 靠左列印
        cout.setf(ios::adjustfield,ios::left) ;

        // 列印非週末日標頭
        cout << setw(5) << " " ;
        for ( d = 1 ; d <= 5 ; ++d ) cout << setw(14) << weekday[d] ;
        cout << endl ;

        // 取出最優先的課程
        foo = course.top() ;

        // 列印課表, 採用橫排節數, 直排日期
        for ( s = 1 ; s <= 8 ; ++s ) {
            cout << setw(3) << s << "  ";

            for ( d = 1 ; d <= 5 ; ++d ) {

                // 如果此日此節有課, 則在列印後, 
                // 再由優先佇列取出一筆資料
                if ( foo.day == d && foo.sct == s ) {
                    cout << setw(14) << foo.name.c_str() ;
                    course.pop() ;
                    if ( ! course.empty() ) foo = course.top() ;
                }
                else 
                    cout << setw(14) << " " ;
            }
            cout << endl ;
        }
        
    }
    
};

// 主函式
int  main() {

    Course_Schedule  courses("class.db") ;

    // 列印課表
    courses.print_schedule() ;

    return 0 ;
    
}

