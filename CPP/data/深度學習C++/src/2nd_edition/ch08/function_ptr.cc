#include <iostream>
#include <iomanip>

using  namespace  std ;

// fn(x) = x * x
double  square( double x ) { return  x * x ; }

// fn(x) = ( x - 1 ) ( x - 1 )
double  f     ( double x ) { return  x * x - 2. * x + 1. ; }

//  c ︽ ㄧΑ fn 跋丁 [a,b] ぇ, 跋丁盢ち澄Θ division 单
void  print_function( double (*fn)(double) , double a , double b , 
                      int division = 20 , int c = 3 ) {

    int     i , j ;
    
    // 夹繷
    for ( i = 0 ; i < c ; ++i ) 
        cout << setw(6) << " X  " << setw(7) << "F(X)" 
             << setw(4) << " " ;
    cout << endl ;

    for ( i = 0 ; i < c ; ++i ) 
        cout << setw(6) << "====" << setw(7) << "====" 
             << setw(4) << " " ;
    cout << endl ;

    // n ㄧΑ翴计
    int     n = division + 1 ;

    // x ㄧΑ跑计, dx –单
    double  x = a ;
    double  dx = ( b - a ) / division ;

    // 璸衡程ぶ斗璶陪ボ计 r (row) 
    int  r = n / c ;
    if ( r * c < n ) r++ ;   
    
    // 程︽┮斗璶陪ボ计
    int  s =  n - r * (c-1) ;

    // 疊翴计计计 2 块, 计计ぃì场干 0 
    cout << fixed << setprecision(2) ;
    
    //  r  (row)
    for ( j = 1 ; j <= r ; ++j , x += dx ) {

        // 玡 c-1 ︽ (column)
        for ( i = 0 ; i < c-1 ; ++i ) 
            cout << setw(6) << x+(r*i)*dx << setw(7) << fn(x+(r*i)*dx) 
                 << setw(4) << " " ;

        // 程︽
        if ( j <= s ) cout << setw(6) << x+(r*(c-1))*dx 
                           << setw(7) << fn(x+(r*(c-1))*dx) ;

        cout << endl ;

    }
}

int main() {

    //   x*x  [0,1] 计, 箇﹚ 20 单ち澄, の 3 ︽
    cout << "> X*X : " << endl ;
    print_function( square , 0 , 1 ) ;
    cout << endl ;
    
    //  (x-1)(x-1)  [0,3] 计,  30 单ち澄,  4 ︽
    cout << "> (X-1)(X-1) : " << endl ;
    print_function( f , 0 , 3 , 30 , 4 ) ;
    
    return 0 ;
    
}

