#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std ;

// 設定函數
double  g( double x ) {  return  sin(x)/x ; }

// 定義位置列舉型別
enum  Position { upperleft , upperright , lowerleft , lowerright };

// 定義函式繪圖樣板類別
template <int row = 21 , int col = 75>
class  Plot_Function {

  private :

    // 儲存點矩陣圖形
    string  bitmap[row+2] ;
    
    // 圖式顯示位置
    Position  caption_location ;
    
    // 儲存函式
    double  (*fn)(double) ;
    string   fn_name ;
    
    // X 的最大值與最小值   f(X) 的最大值與最小值
    double  xmax , xmin ;
    double  ymax , ymin ;

    // 產生點矩陣圖形
    void  plot_bitmap() ;
    
    // 設定 X 與 Y 的最大值與最小值
    void  setup_caption() ;

  public :
    
    // 建構函式
    Plot_Function( double (*f)(double) , string name , 
                   double a , double b , 
                   Position loc = upperleft ) ;

    // 重新設定 X 的最小值與最大值, 即 X 在 [a,b] 之間, 
    // 同時也可以設定輸出的位置
    void assign( double a , double b , Position loc = upperleft ) ;
    
    // 覆載輸出運算子
    template <int r, int c>
    friend ostream& operator << ( ostream& out , 
                                  const Plot_Function<r,c>& foo ) ;

};


int main() {

    // 在 17 列 61 行的格點上畫出函數 g(x) = sin(x)/x 在 [-10,10] 
    // 之間的圖形
    Plot_Function<17,61>  plot( g , "sin(x)/x" , -10 , 10 ) ;

    // 繪圖
    cout << plot << endl ;

    // 設定 X 在 [-3,20] 的圖, 且將圖示放在左上角
    plot.assign(-3,20,upperright) ;

    // 繪圖
    cout << plot << endl ;

    return 0 ;

}

// 建構函式
template <int row , int col>
Plot_Function<row,col>::Plot_Function( double (*f)(double) , 
              string name , double a , double b , Position loc ) 
    : fn(f) , xmin(a) , xmax(b) , caption_location(loc) {

    // 轉成大寫
    for ( int i = 0 ; i < name.size() ; ++i ) 
        if ( name[i] >= 'a' && name[i] <= 'z' ) 
            name[i] = name[i] - 'a' + 'A' ;
    
    fn_name = "F(X)  =  " + name ;
    
    // 產生點矩形圖
    plot_bitmap() ;

    // 產生圖示
    setup_caption() ;

}

// 重新設定 X 的最小值與最大值, 即 X 在 [a,b] 之間, 同時也可以
// 設定輸出的位置
template <int row , int col>
void  Plot_Function<row,col>::assign( double a , double b , 
                                      Position loc ) {
    xmin = a ;
    xmax = b ;
    caption_location = loc ;
    plot_bitmap() ;
    setup_caption() ;
}


// 產生點矩陣圖形
template<int row, int col>
void  Plot_Function<row,col>::plot_bitmap() {

    int  i , r , c ;

    // 起始設定 bitmap 字串陣列
    for ( r = 0 ; r < row+2 ; ++r ) bitmap[r].assign(col+2,' ') ;

    // nx , ny : x 與 y 軸的區間數
    int     nx = col-1 , ny = row-1 ;

    // dx : x 軸上的每一個區間大小
    double  dx = (xmax-xmin)/nx ;

    double  x , y[col] ;

    ymin = 1.e20 ;
    ymax = -ymin ;

    // 計算函數值並找出函數的最大值與最小值
    for ( i = 0 ; i < col ; ++i ) {
        x    = xmin+i*dx ;
        y[i] = fn(x) ;
        if ( y[i] > ymax ) ymax = y[i] ;
        if ( y[i] < ymin ) ymin = y[i] ;
    }

    // dy : y 軸上的每一個區間的大小
    double dy = (ymax-ymin)/ny ;

    // ic : y 軸的下標值
    // ir : x 軸的下標值
    int  ic = static_cast<int>(-xmin/dx+0.5) ; 
    int  ir = static_cast<int>(-ymin/dy+0.5) ; 

    // 畫出 x 軸
    if ( 0 <= ir && ir < row ) {
        for ( c = 0 ; c < col ; ++c ) bitmap[ir][c] = '-' ;
        bitmap[ir][col] = '>' ;
        bitmap[ir][col+1] = 'X' ;
    }
        
    // 畫出 y 軸
    if ( 0 <= ic && ic < col ) {
        for ( r = 0 ; r < row ; ++r ) bitmap[r][ic] = '|' ;
        bitmap[row][ic] = '^' ;
        bitmap[row+1][ic] = 'Y' ;
        if ( 0 <= ic && ic < col ) bitmap[ir][ic] = '+' ;
    }
        
    // 產生函數點
    for ( int  c = 0 ; c < col ; ++c ) {
        bitmap[static_cast<int>((y[c]-ymin)/dy+0.5)][c] = '*' ;
    }

}


// 設定 X 與 Y 的最大值與最小值
template<int row, int col>
void  Plot_Function<row,col>::setup_caption() {

    int r , c ;
    if ( caption_location == upperleft ) {
        r = row ;
        c = 2 ;
    } else if ( caption_location == upperright ) {
        r = row ;
        c = col-18 ;
    } else if ( caption_location == lowerleft ) {
        r = 4 ;
        c = 2 ;
    } else {
        r = 4 ;
        c = col-18 ;
    }

        
    bitmap[r+1].replace( c , fn_name.size() , fn_name ) ;

    ostringstream  ostr ;

    ostr << "Max Y = " << setw(10) << setprecision(3) 
         << right << scientific << ymax ;
    bitmap[r].replace(c,ostr.str().size(),ostr.str()) ;
    
    ostr.str("") ;
    ostr << "Min Y = " << setw(10) << setprecision(3) 
         << right << scientific << ymin ;
    bitmap[r-1].replace(c,ostr.str().size(),ostr.str()) ;
    
    ostr.str("") ;
    ostr << "Max X = " << setw(10) << setprecision(3) 
         << right << fixed << xmax ;
    bitmap[r-2].replace(c,ostr.str().size(),ostr.str()) ;

    ostr.str("") ;
    ostr << "Min X = " << setw(10) << setprecision(3) 
         << right << fixed << xmin ;
    bitmap[r-3].replace(c,ostr.str().size(),ostr.str()) ;
}
    
// 覆載輸出運算子
template <int row, int col>
ostream& operator << ( ostream& out , 
                       const Plot_Function<row,col>& foo ) {

    out << string(col+6,'=') << "\n" ;
    for ( int j = row+1 ; j >= 0 ; --j ) 
        out << "I " << foo.bitmap[j] << " I" << "\n" ;
    out << string(col+6,'=') << "\n" ;

    return out ;
    
}
