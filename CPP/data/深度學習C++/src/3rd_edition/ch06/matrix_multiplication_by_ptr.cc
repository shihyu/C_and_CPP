#include <iostream>
#include <iomanip>

using namespace std ;

int main() {
    
    int i , j , k , sum ;

    // 矩陣大小
    const int ROW_A = 2 , COL_A = 3 ;
    const int ROW_B = 3 , COL_B = 2 ;

    // 定義兩矩陣及其乘積矩陣    
    int a[ROW_A][COL_A] = { { 1 , 2 , 1 } , { 2 , 1 , 1 } } ;
    int b[ROW_B][COL_B] = { { 2 , 3 } , { 2 , 1 } , { 0 , 2 } } ;
    int c[ROW_A][COL_B] ;
    
    // 定義三個指標分別指到矩陣首位元素
    int  *pa , *pb , *pc ;

    pa = &a[0][0] ;
    pb = &b[0][0] ;
    pc = &c[0][0] ;
    
    // 計算乘積結果
    for ( i = 0 ; i < ROW_A ; ++i ) {
        for ( j = 0 ; j < COL_B ; ++j ) {
            sum = 0 ;
            for ( k = 0 ; k < COL_A ; ++k ) {
                sum += *(pa+i*COL_A+k) * *(pb+k*COL_B+j) ;
            }
            *(pc+i*COL_B+j) = sum ;
        }
    }

    // 列印矩陣 a
    for ( i = 0 ; i < ROW_A ; ++i ) {
        for ( j = 0 ; j < COL_A ; ++j ) {
            cout << *(pa+i*COL_A+j) <<  " " ;
        }
        cout << endl ;
    }

    cout << '\n' ;

    // 列印矩陣 b
    for ( i = 0 ; i < ROW_B ; ++i ) {
        for ( j = 0 ; j < COL_B ; ++j ) {
            cout << *(pb+i*COL_B+j) <<  " " ;
        }
        cout << endl ;
    }

    cout << '\n' ;

    // 列印矩陣乘積 c
    for ( i = 0 ; i < ROW_A ; ++i ) {
        for ( j = 0 ; j < COL_B ; ++j ) {
            cout << *(pc+i*COL_B+j) <<  " " ;
        }
        cout << endl ;
    }

    return 0 ;
    
}

            
