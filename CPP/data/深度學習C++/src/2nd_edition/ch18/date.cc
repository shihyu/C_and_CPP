class  Date {
    
  private :

    // 類別靜態資料 : 非閏年的每月總天數
    static  const  int  Days[12] ;
    
    // 年 , 月 , 日
    int  year , mon , day ;

    // 檢查某年是否有閏月
    bool  leap_year ( int y ) const {
        return ( y % 400 == 0 || ( y % 4 == 0 && y % 100 != 0 ) ? 
                 true : false ) ;
    }

  public :
    
    // 建構函式
    Date () {}
    Date ( int y , int m , int d ) : year(y) , mon(m) , day(d) {}

    // 計算出隔一天的日期
    Date  next_date() const ;
    
    // 檢查是否兩天為同一天
    bool  operator == ( const Date& date ) const {
        return ( year == date.year && mon == date.mon && 
                 day == date.day ) ;
    }

    // 檢查是否兩個日期為不同一天
    bool  operator != ( const Date& date ) const { 
        return ! ( *this == date ) ;
    }

    // 檢查兩天時間的前後次序是否為正確
    bool  operator < ( const Date& date ) const ;

    bool  operator <= ( const Date& date ) const { 
        return  *this == date || *this < date ;
    }
    
    // 夥伴函式 : 計算兩個日期相差的天數
    friend  int  operator - ( const Date& , const Date& ) ;
    
    // 夥伴函式 : 輸入與輸出日期
    friend  ostream& operator << ( ostream& , const Date& ) ;
    friend  istream& operator >> ( istream& ,       Date& ) ;

    // 夥伴類別 : 設定類別 Account 為 Date 的夥伴類別
    friend  class  Account ;

};

// 非閏年的每月總天數
const int  Date::Days[12] = { 31 , 28 , 31 , 30 , 31 , 30 , 
                              31 , 31 , 30 , 31 , 30 , 31 } ;

// 計算出隔一天的日期
Date  Date::next_date() const {

    // 當月份的總天數
    int  days_of_month = ( mon == 2 && leap_year( year ) ? 
                           Days[mon-1]+1 : Days[mon-1] ) ;

    int  y = year , m = mon , d = day ;

    // 檢查是否為月底最後一天
    if ( day == days_of_month ) {
        d = 1 ;  ++m ;
        // 若為年尾, 則次日為隔年第一天
        if ( m > 12 ) {  m = 1 ;  y += 1 ; } 
    } else 
        d++ ;

    return  Date( y , m , d ) ;

}

// 檢查兩天時間的前後次序是否為正確
bool  Date::operator < ( const Date& date ) const {

    if ( year == date.year ) {

        if ( mon == date.mon ) 
            return ( day < date.day ? true : false ) ;
        else 
            return ( mon < date.mon ? true : false ) ;

    } else 

        return ( year < date.year ? true : false ) ;

}

// 計算兩天相差的天數
int   operator - ( const Date& date1 , const Date& date2 )  {

    int  c = 0 ;
    Date date ;

    if ( date1 < date2 ) {
        
        for ( date = date1 ;  date != date2 ; ++c ) 
            date = date.next_date() ;

        return -c ;
        
    } else {
        
        for ( date = date2 ;  date != date1 ; ++c ) 
            date = date.next_date() ;
        return c ;

    }
    
}
    
// 日期的輸出運算子
ostream& operator << ( ostream& out , const Date& date ) {
    return out << date.year << '-' 
               << setw(2) << setfill('0') << date.mon << '-' 
               << setw(2) << date.day << setfill(' ') ;
}

// 日期的輸入運算子
istream& operator >> ( istream& in , Date& date ) {
    char  sep ;
    return  in >> date.year >> sep >> date.mon >> sep >> date.day ;
}
