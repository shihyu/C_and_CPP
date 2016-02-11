#include <iostream>
#include <vector>

using namespace std ;

template  <class T>
class   Matrix {

  private :

    vector< vector<T> >  mat ;            // 雙重向量陣列
    int                  row , col ;      // 列數與行數   

  public :

    // 預設建構函式
    Matrix() : row(0) , col(0) {}

    // 建構函式
    Matrix( int r , int c , const T& val = 0 ) : row(r) , col(c) {
        mat = vector< vector<T> >(r,vector<T>(c,val)) ;
    }

    // 回傳矩陣列數與行數
    inline  int  rows() const {  return row ;  }
    inline  int  cols() const {  return col ;  }
    
    // 回傳矩陣的第 i 列的向量陣列參考
    inline vector<T>&        operator [] ( int i )       { 
        return  mat[i] ; 
    }

    inline const vector<T>&  operator [] ( int i ) const { 
        return  mat[i] ; 
    }

    // 重載 += 運算子
    Matrix<T>&   operator += ( const Matrix<T>& rhs ) {
        int  i , j ;
        for ( i = 0 ; i < row ; ++i ) {
            for ( j = 0 ; j < col ; ++j ) mat[i][j] += rhs[i][j] ;
        }
        return  *this ;
    }
    
};


// 定義矩陣的輸出運算子
template <class S>
ostream&  operator << ( ostream& out , const Matrix<S>& m ) {

    int  i , j ;
    for ( i = 0 ; i < m.rows() ; ++i ) {
        out << '\n' ;
        for ( j = 0 ; j < m.cols() ; ++j ) {
            out << m[i][j] << "  " ;
        }
    }
    return  out << '\n' ;
}

// 重載矩陣乘法運算子
template  <class T>
Matrix<T>  operator * ( const Matrix<T>& m1 , 
                        const Matrix<T>& m2 ) {

    T          sum ;
    int        i , j , k ;
    Matrix<T>  m(m1.rows(),m2.cols()) ;
 
    for ( i = 0 ; i < m1.rows() ; ++i ) {
        for ( j = 0 ; j < m2.cols() ; ++j ) {
            sum = 0 ;
            for ( k = 0 ; k < m1.cols() ; ++k ) 
                sum += m1[i][k] * m2[k][j] ;
            m[i][j] = sum ;
        }
    }
    return  m ;
}

// 重載矩陣加法運算子
template  <class T>
Matrix<T>  operator + ( const Matrix<T>& m1 , 
                        const Matrix<T>& m2 ) {
    Matrix<T>  m = m1 ;
    return  m += m2 ;
}

int  main() {

    // A 為 2 x 3 矩陣,  B 為 3 x 2 矩陣
    Matrix<int>  A(2,3,1) , B(3,2,2) ;
    
    cout << "A = "       << A << '\n' ;
    cout << "B = "       << B << '\n' ;
    cout << "A * B = "   << A * B << '\n' ;
    cout << "A + A = "   << A + A << '\n' ; 
    cout << "A[1][2] = " << A[1][2] << '\n' ;

    return 0 ;
    
}
