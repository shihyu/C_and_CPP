#include <iostream>
#include <cstdlib>
#include <string>

using  namespace  std ;

// 定義錯誤證件號碼處理類別
class  ID_ERR {

  private :

    int  kind ;

  public :

    // 建構函式
    ID_ERR( int i ) : kind(i) {} ;

    // 錯誤訊息
    char*  error_msg() const {
        switch ( kind ) {
          case 0 : return "證件字號長度不對" ;
          case 1 : return "第一個字元須為英文字母" ;
          case 2 : return "第一個數字須要是 1 或 2" ;
          case 3 : return "第二個數字以後須要在 0 至 9 之間" ;
          case 4 : return "檢查碼錯誤" ;
        }
    }

} ;

// 檢查輸入的證件號碼是否正確
bool  correct_id ( string id ) throw(ID_ERR) {

    // 設定加權數為莫扎特生年 (1756), 卒年 (1791) 與享年 (35)
    static const int mozart[10] = { 1 , 7 , 5 , 6 , 1 , 7 , 9 , 
                                    1 , 3 , 5 };

    int  no[10] , i , tmp , sum ;  

    // 如果長度不對, 則擲出第零類錯誤
    if ( id.size() != 10 ) throw  ID_ERR(0) ;

    for ( i = 0 ; i < 9 ; ++i ) {
        
        if ( i == 0 ) {

            // 將第一個字母由小寫轉成大寫
            if ( ( id[0] >= 'a' ) && ( id[0] <= 'z' ) )  
                id[0] += 'A' - 'a' ;

            // 如果第一個字母不是英文字母, 則擲出第一類錯誤
            if ( ( id[0] < 'A' ) || ( id[0] > 'Z' ) )  
                throw  ID_ERR(1) ;

            // 將字母對應成數字 1 到 26
            tmp = id[0] - 'A' + 1 ;
            no[0] = tmp / 10 ;
            no[1] = tmp % 10 ;

        } else if ( i == 1 ) {

            // 如果第一個數字不是 1 或者 2, 則擲出第二類錯誤
            if ( ! ( id[1] == '1' || id[1] == '2' ) ) 
                throw  ID_ERR(2) ;

            no[2] = id[1] - '0' ;
            
        } else {

            // 如果其它的字元不為數字, 則擲出第三類錯誤
            if ( id[i] < '0' || id[i] > '9' ) throw  ID_ERR(3) ;
            no[i+1] = id[i] - '0' ;

        }

    }

    // 計算出正確的檢查號碼
    sum = no[0] ;
    for ( i = 1 ; i < 10 ; ++i ) sum += no[i] * mozart[i]  ;
    sum = sum % 10  ;
    
    // 如果檢查碼不正確, 則擲出第四類錯誤
    if ( sum != ( id[9] - '0' ) ) throw  ID_ERR(4) ;
    
    return  true ;
    
}

int  main() {

    string  id ;

    while ( 1 ) {
        
        cout << "> 請輸入證件號碼 : " ;
        cin  >> id ;

        try {  
            if ( correct_id(id) ) cout << "> 正確字號\n\n" ;
            return 0 ;
        }

        catch ( const ID_ERR& e ) { 
            cout << "> 錯誤 : " << e.error_msg() << "\n\n" ; 
        }
    }

    return 0 ;
    
}
