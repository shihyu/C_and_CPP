#include <iostream>
#include <cstdlib>
#include <string>

using namespace std ;

// string 字串轉 wstring 字串
wstring  str2wstr( const string& from ) {

    // 末尾加上 1 個空字元長度
    int  wcsize = from.size()+1 ;
    wchar_t  *to = new wchar_t[wcsize] ;

    // 多位元組傳統字串轉為寬字元字串
    mbstowcs(to,from.c_str(),wcsize) ;

    wstring  wstr = to ;
    delete [] to ;

    return wstr ;

}


// wstring 字串轉 string 字串
string  wstr2str( const wstring& from ) {

    // 末尾加上 1 個空字元長度
    int  csize = sizeof(wchar_t)*from.size()+1 ;
    char *to = new char[csize] ;

    // 寬字元字串轉為多位元組傳統字串
    wcstombs(to,from.c_str(),csize) ;
    
    string  str = to ;
    delete [] to ;

    return str ;

}


int main() {

    setlocale( LC_ALL , "zh_TW.UTF-8" ) ;
    
    // 字串 
    string  a = "=== 山高月小  水落石出 ===" , b ;

    b = wstr2str( str2wstr(a) ) ;

    // 寬字串
    wstring  c = L"=== 山高月小  水落石出 ===" , d ;

    d = str2wstr( wstr2str(c) ) ;


    // 以下兩者則一列印

    // (1) 
    if ( a == b ) cout << "(1) string : " << b << endl ;
    
    // (2) 
    // if ( c == d ) wcout << "(2) wstring : " << d << endl ;

    return 0 ;

}
