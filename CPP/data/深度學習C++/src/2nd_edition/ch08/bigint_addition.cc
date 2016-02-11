#include <iostream>
#include <string>

using namespace std ;

// ﹃俱计
string  bigint_addition( string a , string b ) {

    int  i , tmp ;
    
    // 璸衡ㄢ计﹃畉
    int  size_difference = a.length() - b.length() ;

    if ( size_difference < 0 ) size_difference *= -1 ;

    // 盢耕祏计﹃ぇ玡干じ 0 , ㄏ眔程ㄢ﹃单
    if ( a.length() > b.length() ) 
        for ( i = 0 ; i < size_difference ; ++i ) b = '0' + b ;
    else
        for ( i = 0 ; i < size_difference ; ++i ) a = '0' + a ;
    
    string    sum = "" ;    // ﹃计㎝
    int     carry = 0  ;    // 猭秈计

    // パ﹃程Юじ┕玡, 盢秈计 carry 跑计い
    for ( i = a.length()-1 ; i >= 0 ; --i ) {
        tmp = ( b[i] - '0' ) + ( a[i] - '0' ) + carry ;
        sum = static_cast<char>(( tmp % 10 + '0' )) + sum ;
        carry =  tmp / 10 ;
    }

    // 矪瞶程逞秈计
    if ( carry ) sum = static_cast<char>( carry + '0' ) + sum ;
    
    return sum ;

}

int  main() {
    
    string  a , b ;
    
    cout << "> 块ㄢタ俱计 : " ;
    cin  >> a >> b ;
    
    cout << '\n' << a << " + " << b << " = " 
         << bigint_addition(a,b) << endl ;

    return 0 ;
    
}
