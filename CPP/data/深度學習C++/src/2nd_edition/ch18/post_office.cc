#include <iostream>
#include <iomanip>
#include <vector>

using namespace std ;

// 將在同目錄的日期檔案程式碼加入
#include "date.cc" 

// 個人帳號資料
class  Account {

  private :

    static  double  interest_rate            ;   // 年利率
    
    int             transaction_no           ;   // 交易次數
    vector<bool>    is_interest              ;   // 是否交易為
                                                 // 利息收入
    vector<double>  balance                  ;   // 餘額
    vector<double>  transaction              ;   // 交易金額
    vector<Date>    transaction_date         ;   // 交易日期
    
    // 計算某年的第幾期的所得利息
    void  add_interest( int year , int time ) {

        // 每日利息
        double daily_interest_rate = interest_rate / 365 ;
        
        int i , index ;
        int day_count ;
        
        // 由所有的資料中, 找尋存有某年第幾期的第一筆資料下標
        for ( i = 0 ; i < transaction_no ; ++i ) {
            if ( transaction_date[i].year == year ) {
                if ( time == 1 ) {
                    if ( transaction_date[i].mon <= 6 ) index = i ;
                } else {
                    if ( transaction_date[i].mon > 6 )  index = i ;
                }
            }
        }

        // 記錄利息的收入日期
        if ( time == 1 ) 
            transaction_date.push_back( Date(year,7,1) ) ;
        else
            transaction_date.push_back( Date(year+1,1,1) ) ;

        
        // 計算天數與利息
        double  interest = 0 ;
        for ( i = index ; i < transaction_no ; ++i ) {
            day_count = transaction_date[i+1] - transaction_date[i] ;
            interest += balance[i] * day_count * daily_interest_rate;
        }

        // 更新資料
        is_interest.push_back( true ) ;
        transaction.push_back( interest ) ;
        balance.push_back( balance.back() + interest ) ;
        transaction_no = transaction.size() ;

    }
    
    // 列印交易標頭
    void  print_transaction_header() const {
        cout << setw(6) << "日期" << setw(14) << "註解" 
             << setw(15) << "存款" << setw(15) << "提款" 
             << setw(15) << "餘額" << '\n' ;
    }

    // 列印單筆交易細目
    void  print_single_transaction( int i ) const {

        cout << transaction_date[i] 
             << setw(10) << ( is_interest[i] ? "利息" : " " ) ;

        cout.setf(ios::fixed,ios::floatfield) ;
        
        if ( transaction[i] >= 0. ) 
            cout << setw(15) << setprecision(2) << transaction[i] 
                 << setw(15) << " " ;
        else
            cout << setw(15) << " " << setw(15) << setprecision(2) 
                 << transaction[i] ;
        
        cout << setw(15) << balance[i] << setprecision(0) << '\n' ;

        cout.unsetf(ios::fixed) ;

    }
    

  public :

    // 設定物件    
    Account() : transaction_no(0) {}
    
    // 列印所有交易細目
    void  print_all_transactions() const {
        print_transaction_header() ;
        for ( int i = 0 ; i < transaction_no ; ++i ) {
            print_single_transaction(i) ;
        }
    }

    // 交易處理    
    bool  make_transaction( const Date& today , double amount ) {

        // 如果已經有交易記錄
        if ( transaction_no ) {

            // 上次交易時間
            Date  date = transaction_date.back() ;

            if ( today < date ) {
                cout << "> 輸入的日期已經過期\n" ;
                return false ;
            }

            print_transaction_header() ;

            // 計算利息
            bool  first_day = true ;
            while ( date <= today ) {

                if ( ( date.mon ==  7 && date.day == 1 ) ||
                     ( date.mon ==  1 && date.day == 1 ) ) {
                    if ( ! first_day ) {
                        if ( date.mon ==  7 ) 
                            add_interest( date.year , 1 ) ;
                        else 
                            add_interest( date.year-1 , 2 ) ;

                        print_single_transaction(transaction_no-1) ;
                    }
                }

                date = date.next_date() ;
                first_day = false ;
            }

            // 存款不足
            if ( -amount > balance.back() ) return false ;

            balance.push_back( balance.back() + amount ) ;

        } else {

            // 第一次交易, 不能提款
            if ( amount < 0. ) return false ;

            print_transaction_header() ;
            balance.push_back( amount ) ;
            
        }
        
        // 更新資料
        is_interest.push_back( false ) ;
        transaction_date.push_back( today ) ;
        transaction.push_back( amount ) ;

        // 列印此次交易資料
        print_single_transaction(transaction_no) ;
        transaction_no = transaction.size() ;
        return true ;
        
    }

    // 列印交易訊息
    void  print_transaction_message() const {
        cout << "> 歡迎使用個人專用虛擬郵局, 請選擇以下服務項目\n" 
             << "  [1] 存款交易    [2] 提款交易  " 
             << "  [3] 列印明細    [4] 離開\n" ;
    }

};

// 設定利息
double  Account::interest_rate = 0.1 ;

int main() {
    
    int      option ;
    
    Account  foo    ;
    Date     date   ;
    double   amount ;
    
    while ( 1 ) {
        
        foo.print_transaction_message() ;
        cout << "> " ;
        cin >> option ;
        
        if ( option == 1 || option == 2 ) {

            // 存款 與 提款
            cout << "> 輸入日期與金額 : " ;
            cin >> date >> amount ;

            // 讓提款的金額為負值
            if ( option == 2 && amount > 0. ) amount *= -1 ;

            foo.make_transaction(date,amount) ;

        } else if ( option == 3 ) {

            // 列印所有交易明細
            foo.print_all_transactions() ;

        } else {

            // 結束
            break ;

        }

        cout << endl ;
        
    }

    return 0 ;
    
}

