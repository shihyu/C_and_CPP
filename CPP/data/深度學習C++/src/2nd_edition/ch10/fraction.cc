#include <iostream>
#include <cassert>

using namespace std ;

// 荡癸
int abs( int a ) { return a > 0 ? a : -a ;  }
    
class  Fraction {

  private :

    // だ籔だダ  ( だダ > 0 )
    int  num , den ;  

    // 程そ计
    int  gcd( int a , int b ) const {
        assert( a > 0 && b > 0 ) ;
        if ( a > b ) 
            return  ( a % b == 0 ? b : gcd( b , a % b ) ) ; 
        else 
            return  ( b % a == 0 ? a : gcd( a , b % a ) ) ; 
    }

  public :

    // ず﹚篶ㄧΑ
    Fraction() {};

    // 篶ㄧΑ : だダぃ单箂
    Fraction( int n , int d = 1 ) : num(n) , den(d) {
        assert( d != 0 ) ;
        if ( den < 0 ) { num *= -1 ; den *= -1 ; }
    }
    
    // 盿だ计篶ㄧΑ : だ单箂, だダ箂
    Fraction( int a , int n , int d ) : den(d) {
        assert( d > 0 && n >= 0 ) ;
        num = ( a > 0 ? a * d + n : a * d - n ) ;
    }

    // 癳だ籔だダ
    int  get_den() const { return den ; }
    int  get_num() const { return num ; }

    // ΘㄧΑ : 璽腹
    Fraction  operator-() {  return  Fraction(-num,den) ; }

    // ΘㄧΑ : += , -= , *= , /=
    Fraction& operator+= ( const Fraction& a ) ;
    Fraction& operator-= ( const Fraction& a ) ;
    Fraction& operator*= ( const Fraction& a ) ;
    Fraction& operator/= ( const Fraction& a ) ;

    // 块笲衡  : 钡 だ / だダ Α
    friend istream& operator >> ( istream& in , Fraction& foo ) {
        char  slash ;
        in >> foo.num >> slash  >> foo.den ;
        if ( foo.den < 0 ) { foo.num *= -1 ;  foo.den *= -1 ; }
        return in ;
    }
    
    // 块笲衡  : 块だだ计
    friend ostream& operator << ( ostream& out , 
                                  const Fraction& foo ) {
        int  num = ( foo.num > 0 ? foo.num : -foo.num ) ;
        int  den = foo.den ;
        int  divisor = ( num == 0 ? 1 : foo.gcd(num,den) ) ;
        return  out << foo.num/divisor << "/" << den/divisor ;
    }
    
} ;

// 办ㄧΑ + 
Fraction  operator+ ( const Fraction& a , const Fraction& b ) {
    return  
      Fraction( a.get_num()*b.get_den() + a.get_den()*b.get_num() ,
                a.get_den()*b.get_den() ) ;
}

// 办ㄧΑ - 
Fraction  operator- ( const Fraction& a , const Fraction& b ) {
    return  
      Fraction( a.get_num()*b.get_den() - a.get_den()*b.get_num() ,
                a.get_den()*b.get_den() ) ;
}

// 办ㄧΑ * 
Fraction  operator* ( const Fraction& a , const Fraction& b ) {
    return  Fraction( a.get_num() * b.get_num() , 
                      a.get_den() * b.get_den() ) ;
}

// 办ㄧΑ /
Fraction  operator/ ( const Fraction& a , const Fraction& b ) {
    return  Fraction( a.get_num() * b.get_den() , 
                      a.get_den() * b.get_num() ) ;
}

// ΘㄧΑ += : ノΤ operator +
Fraction&  Fraction::operator+= ( const Fraction& a ) { 
    return *this = *this + a ; 
}

// ΘㄧΑ -= : ノΤ operator -
Fraction&  Fraction::operator-= ( const Fraction& a ) { 
    return *this = *this - a ; 
}

// ΘㄧΑ *= : ┪︽砞璸
Fraction&  Fraction::operator*= ( const Fraction& a ) { 
    num = num * a.num ;  den = den * a.den ;  
    return *this ;
}

// ΘㄧΑ /= : ┪︽砞璸
Fraction&  Fraction::operator/= ( const Fraction& a ) { 
    num = num * a.den ;  den = den * a.num ;  
    if ( den < 0 ) { num *= -1 ; den *= -1 ; }
    return *this ;
}

// 办ㄧΑ : 玡竚患糤
Fraction&  operator++( Fraction& a ) {
    return  a += 1 ;
}

// 办ㄧΑ : 
bool  operator< ( const Fraction& a , const Fraction& b ) { 
    return  a.get_num()*b.get_den() < b.get_num()*a.get_den() ;
}
        
int main() {
        
    Fraction  a(2,3) , b(-1,3,2) , c(10,-6) ;
    
    cout << "> a = " << a << " , b = " << b 
         << " , c = " << c << endl ;

    cout << "> 2 + a * -b - c * b / 2 = " 
         << 2 + a * -b - c * b / 2 << "\n\n" ;

    a += b -= c + 2 ;
    cout << "> a += b -= c + 2 : " << '\n' 
         << "  a = " << a << " , b = " << b 
         << " , c = " << c << "\n\n" ;

    for ( Fraction d(0,1) ; d < 5 ; ++d ) cout << d << " " ;
    cout << "\n\n" ;
    
    cout << "> 块 だ/だダ Α : " ;
    cin >> a ;
    cout << "> 块 : " << a << endl ;

    return 0 ;
    
}

