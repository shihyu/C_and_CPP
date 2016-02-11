#include <iostream>
#include <iomanip>

using namespace std ;

int main() {
    
    int  F , O , R , T , Y , E , N , S , I , X ;
    int  i , j , t , y ;
    int  forty , ten , sixty ;

    // 癹伴パ程计程计
    for ( i = 10234 ; i < 98766 ; ++i ) {

        // だ璸衡计, の浪琩ㄤ计ぃ狡

        F = i / 10000 ;  

        O = ( i / 1000 ) % 10 ;
        if ( O == F ) continue ;

        R = ( i / 100  ) % 10 ;
        if ( R == F || R == O ) continue ;
        
        T = ( i / 10   ) % 10 ;
        if ( T == F || T == O || T == R ) continue ;
        
        Y = i % 10 ;
        if ( Y == F || Y == O || Y == R || Y == T ) continue ;

        forty = F * 10000 + O * 1000 + R * 100 + T * 10 + Y ;
        
        for ( j = 1 ; j < 99 ; ++j ) {

            E = j / 10 ;
            if ( E == F || E == O || E == R || E == T || E == Y ) 
                continue ;
            
            N = j % 10 ;
            if ( N == F || N == O || N == R || N == T || N == Y || 
                 N == E )  continue ;

            ten = T * 100 + E * 10 + N ;

            sixty = forty + ten + ten ;
        
            S = sixty / 10000 ;        
            I = sixty / 1000 % 10 ;        
            X = sixty / 100 % 10 ;
            t = sixty / 10 % 10 ;
            y = sixty % 10 ;

            if ( y != Y || t != T ) continue ;

            if ( S == F || S == O || S == R || S == T || S == Y ||
                 S == E || S == N ) continue ;

            if ( I == F || I == O || I == R || I == T || I == Y ||
                 I == E || I == N || I == S ) continue ;

            if ( X == F || X == O || X == R || X == T || X == Y ||
                 X == E || X == N || X == S || X == I ) continue ;

            // 挡狦
            cout << setw(10) << forty << endl 
                 << setw(10) << ten << endl 
                 << setw(3)  << " +"  << setw(7) << ten << endl 
                 << setw(11) << " ---------" << endl
                 << setw(10) << sixty << endl ;
            
        }

    }

    return 0 ;
    
}
