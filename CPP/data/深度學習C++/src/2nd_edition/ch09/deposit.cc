#include <iostream>

using namespace std ;

typedef  double  Dollar ;

class  Deposit {

  private :

    // 所有存款帳號的利率
    static  double  interest_rate ;

    // 存款
    Dollar      amount ;

  public :

    // 建構成員函式
    Deposit( Dollar money = 0 ) { amount = money ; }

    // 設定所有存款帳號的新利率
    static  void  set_rate( double rate ) { 
        interest_rate = rate ; 
    }

    // 輸出存款
    Dollar  deposit() const { return  amount ; }

    // 輸出利息
    Dollar  interest() const { return  amount * interest_rate ; } 

} ;

// 設定存款帳號類別的內定靜態資料初值 (也可以不須設初值, 
// 但仍須定義)
double  Deposit::interest_rate = 0.05 ;

int  main() {

    const int no = 5 ;

    // 設定存款帳號
    Deposit  account[no] = { 100 , 300 , 200 , 350 , 50 } ;

    double  interest_rate ;
     
    cout << "> 輸入利率 : " ;
    cin >> interest_rate ;
    
    // 設定存款帳號的新利率 
    Deposit::set_rate(interest_rate) ;

    // 計算總存款與總利息
    double  total_deposit = 0. , total_interest = 0. ;
    for ( int i = 0 ; i < no ; ++i ) {
        total_deposit  += account[i].deposit() ;
        total_interest += account[i].interest() ;
    }

    cout << "> 總存款為 : " << total_deposit  << endl ;
    cout << "> 總利息為 : " << total_interest << endl ;

    return 0 ;
    
}


