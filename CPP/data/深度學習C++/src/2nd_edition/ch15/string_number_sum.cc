#include <iostream>
#include <string>
#include <cstdlib> 

using namespace std ;

int  string_number_sum( const string& line ) {
    
    const  string  number = "0123456789" ;
    
    int j = 0 , i , sum = 0 ;

    while ( 1 ) {
            
        // 由下標 j 起找尋第一個數字的下標 i, 若沒找到, 跳離迴圈
        i = line.find_first_of(number,j) ;
        if ( i == string::npos ) break   ;    

        // 由第一個數字下標 i 起找尋第一個非數字的下標 j
        j = line.find_first_not_of(number,i) ;

        // 如果 j 已經到末端, 則截取最後一個數字後跳離迴圈
        if ( j == string::npos ) {

            // 如果此數字從第一格開始或者是在空格之後  才截取數字
            if ( i == 0 || ( i > 0 && line[i-1] == ' ' ) )
                sum += 
                    atoi( line.substr(i,line.length()-i).c_str() ) ;

            break ;
        }

        // 如果此數字從第一格開始或者是在空格之後  才截取數字
        if ( i == 0 || ( i > 0 && line[i-1] == ' ' ) ) 
            sum += atoi( line.substr(i,j-i).c_str() ) ; 
        
    }

    return  sum ;
        
}

int main() {

    string  line ;

    while ( 1 ) {
        cout << "> " ;
        getline( cin , line ) ;

        // 如果為空行 則跳離迴圈結束
        if ( line.empty() ) break ;
        cout << "> " << string_number_sum( line ) << "\n\n" ;
    } 

    return 0 ;
    
}

