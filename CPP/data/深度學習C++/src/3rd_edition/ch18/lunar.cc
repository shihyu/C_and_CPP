#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std ;


// 分數類別
class  Fraction {
  private :

    // 分子 與 分母
    int  num , den ;

    // 計算最大公因數
    int  gcd( int a , int b ) const {
        if ( a >= b ) 
            return ( a % b == 0 ? b : gcd(b,a%b) ) ;
        else 
            return ( b % a == 0 ? a : gcd(a,b%a) ) ;
    }

    
  public :

    // (1) 約分的建構函式
    Fraction( int n = 0 , int d = 1 ) : num(n) , den(d) {
        if ( num != 0 ) {
            int g = gcd(num,den) ;
            num /= g ;
            den /= g ;
        }
    }

    // (2) 不約分的建構函式
    Fraction( int n , int d , int j ) : num(n) , den(d) {}

    // 回傳分子
    int  get_num() const { return  num ; }

    // 回傳分母
    int  get_den() const { return  den ; }
    
    // 回傳倒數
    Fraction  inverse() const { return  Fraction(den,num) ; }

    // 計算連分數表示數列
    vector<int>  continued_fraction_list() const {

        vector<int>  no ;

        Fraction  foo = *this ;


        do  {
            no.push_back( foo.num/foo.den ) ;
            foo = foo - no.back() ;
            foo = foo.inverse() ;
        } while ( foo.den != 1 ) ;
        
        no.push_back( foo.num ) ;
        
        return  no ;
    }

    // 計算所有漸近分數之值
    vector<Fraction>  generate_convergents() const {
        
        vector<int>       no = continued_fraction_list() ;
        vector<Fraction>  flist(no.size()) ;

        int       i , j ;
        Fraction  sum ;

        flist.front() = Fraction(no[0]) ;
        
        for ( i = 1 ; i < no.size()-1 ; ++i ) {
            sum = Fraction(no[i])  ;
            for ( j = i ; j > 0 ; --j ) 
                sum = no[j-1] + sum.inverse() ;
            flist[i] = sum ;
        }
        
        flist.back() = *this ;
        
        return  flist ;
        
    }

    // 夥伴函式：輸出運算子
    friend  ostream& operator<< ( ostream& out , 
                                  const Fraction& foo ) {
        ostringstream  ostr ;
        if ( foo.num == 0 ) 
            ostr << "0" ;
        else 
            ostr << foo.num << "/" << foo.den ;
        
        return  out << ostr.str() ;
    }

    // 夥伴函式：加法運算子
    friend  Fraction  operator+( const Fraction& a , 
                                 const Fraction& b ) {
        return  Fraction(a.num*b.den+a.den*b.num,a.den*b.den) ;
    }

    // 夥伴函式：減法運算子
    friend  Fraction  operator-( const Fraction& a , 
                                 const Fraction& b ) {
        return  Fraction(a.num*b.den-a.den*b.num,a.den*b.den) ;
    }


};

int main() {
    
    int  i ;
    
    const int MDAYS = 295306 ;
    const int YDAYS = 3652422 ;
    const int SCALE = 10000 ;

    Fraction   foo(YDAYS,MDAYS,0) ;

    vector<int>  no = foo.continued_fraction_list() ;
    vector<Fraction>  cno = foo.generate_convergents() ;

    cout << "> " << foo << " = [" ;
    for ( i = 0 ; i < no.size()-1 ; ++i ) 
        cout << no[i] << ( i == 0 ? ";" : "," ) ;
    cout << no.back() << "] 的漸近分數 : \n" ;

    for ( i = 0 ; i < cno.size() ; ++i ) {
        cout << "[" << setw(2) << i+1 << "] " 
             << setw(14) << cno[i] << "    " ;
        if ( (i+1)%3 == 0 ) cout << endl ;
    }
    cout << "\n\n" ;


    int  M , Y ;
    double         min ;
    
    cout << "> 漸近分數所產生的閏月數 : \n" ;
    for ( i = 0 ; i < cno.size() ; ++i ) {
        M = cno[i].get_num() ;
        Y = cno[i].get_den() ;
        min = ( 1. * MDAYS * M - 1. * YDAYS * Y )*1440/SCALE/Y ;
        
        cout << "[" << setw(2) << i+1 << "] 每 " 
             << setw(6) <<  Y << " 年 " << setw(6) << M - 12 * Y
             << " 個閏月，陰曆平均每年比陽曆"
             << ( min > 0 ? "多" : "少") 
             << setprecision(6) << fixed << setw(13) 
             << ( min >= 0 ? min : -min ) << " 分鐘\n" ;
    }

    return 0 ;
    
}

