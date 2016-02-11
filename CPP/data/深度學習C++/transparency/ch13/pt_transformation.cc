#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <string>

using  namespace  std ;

// 定義角度, 長度, 與距離等類型
typedef  double  Angle ;
typedef  double  Length ;
typedef  double  Distance ;

// 設定 PI
const  double  PI = 3.14159265358979 ;

// 設定轉換類別 : 平移 旋轉 鏡射
enum  Transformation_Type { TRA , ROT , REF } ;

// 幾何座標轉換 : 抽象基礎類別
class  Geometric_Transformation {

  protected :
    
    double  m[2][3] ;  // 轉換矩陣
    
  public :

    // 計算新的轉換矩陣 A = M A : 兩轉換矩陣乘積
    void  update_transformation_matrix( double a[2][3] ) {

        int i , j ;
        
        static  double tmp[2][3] ;
        for ( i = 0 ; i < 2 ; ++i ) 
            for ( j = 0 ; j < 2 ; ++j ) 
                tmp[i][j] = m[i][0] * a[0][j] + m[i][1] * a[1][j] ;

        tmp[0][2] = m[0][0]*a[0][2] + m[0][1]*a[1][2] + m[0][2] ;
        tmp[1][2] = m[1][0]*a[0][2] + m[1][1]*a[1][2] + m[1][2] ;
        
        for ( i = 0 ; i < 2 ; ++i ) 
            for ( j = 0 ; j < 3 ; ++j ) a[i][j] = tmp[i][j] ;
    
    }
    
    // 回傳轉換的類型
    virtual Transformation_Type  get_transformation_type() 
        const = 0 ;

    // 虛擬解構函式
    virtual ~Geometric_Transformation() {}

} ;


typedef  Geometric_Transformation  GT ;


// 平移類別
class  Translation : public GT {

  private :

    Distance  dx , dy ;   // 儲存對 X 與 Y 的平移距離
    
  public :

    // 設定轉換矩陣
    Translation( Distance x , Distance y ) : dx(x) , dy(y) {
        m[0][0] = 1. ;  m[0][1] =  0. ; m[0][2] = dx ;
        m[1][0] = 0. ;  m[1][1] =  1. ; m[1][2] = dy ;
    }

    Transformation_Type get_transformation_type() const {
        return Transformation_Type( TRA ) ;
    }

} ;

// 旋轉類別
class  Rotation : public GT {

  private :

    Angle  angle ;

  public :

    // 設定轉換矩陣, 輸入角度的單位為度
    Rotation( Angle a ) : angle(PI*a/180.)  { 
        double  c = cos(angle) , s = sin(angle) ;
        m[0][0] = c  ;  m[0][1] = -s  ; m[0][2] = 0. ;
        m[1][0] = s  ;  m[1][1] =  c  ; m[1][2] = 0. ;
    };

    Transformation_Type get_transformation_type() const {
        return Transformation_Type( ROT ) ;
    }

};

// 鏡射類別
class  Reflection : public GT {

  private :

    Angle  angle ;

  public :

    // 設定轉換矩陣, 輸入角度的單位為度
    Reflection( Angle a ) : angle(PI*a/180.) {
        double  c = cos(2.*angle) , s = sin(2.*angle) ;
        m[0][0] = c  ;  m[0][1] =  s  ; m[0][2] = 0. ;
        m[1][0] = s  ;  m[1][1] = -c  ; m[1][2] = 0. ;
    };

    Transformation_Type get_transformation_type() const {
        return Transformation_Type( REF ) ;
    }

};


// 平面點
class  Point {

  private :

        double   x , y ;   // 平面點的座標

  public :

    // 建構函式
    Point() {}
    Point( double a , double b ) : x(a) , y(b) {}

    // 回傳點經過一連串的幾何轉換後的座標
    Point  transformation( const vector<GT*>& gt ) const ;

    // 覆載輸入與輸出運算子
    friend  istream&  operator>> ( istream& in , Point& pt ) {
        return  in >> pt.x >> pt.y ;
    }

    friend  ostream&  operator<< ( ostream& out , 
                                   const Point& pt ) {
        return  out << "( " << pt.x << " , " << pt.y << " )" ;
    }
    
} ;

// 回傳點經過一連串的幾何轉換後的座標
Point  Point::transformation( const vector<GT*>& gt ) const {

    // 設定初始的轉換矩陣為單位矩陣
    double  m[2][3] = { {1,0,0},{0,1,0} } ;
     
    // 重複計算每次幾何轉換後的轉換矩陣 m
    for ( int i = 0 ; i < gt.size() ; ++i ) {
        gt[i]->update_transformation_matrix(m) ;
    }

    // 將轉換矩陣乘上原始點座標位置後  產生新點輸出
    return  Point( m[0][0] * x + m[0][1] * y + m[0][2] ,
                   m[1][0] * x + m[1][1] * y + m[1][2] ) ;
    
} ;


int  main() {
    
    // 平面點
    Point  point ;

    // 向量陣列儲存轉換類別物件的指標
    vector<GT*>  gt ;

    int       i , no ;
    Distance  dx , dy ;  
    Angle     angle   ;  // 使用角度, 非徑度
    
    // 讀取資料
    string         line , transformation ;
    istringstream  istr ;

    do {
        
        cout 
        << "> 輸入平面點座標, 轉換次數, 個別轉換方式與相關資料 :"
        << endl ;
    
        // 讀取每一行, 存入字串流物件
        getline(cin,line) ;
        istr.str(line) ;

        // 讀入點座標與須要轉換的次數
        istr >> point >> no ;
        
        // 處理每次的轉換
        for ( i = 0 ; i < no ; ++i ) {

            istr >> transformation ;

            if ( transformation == "TRA" ) {             // 平移
                istr >> dx >> dy ;
                gt.push_back( new Translation(dx,dy) ) ;
            } else if ( transformation == "ROT" ) {      // 旋轉
                istr >> angle ;
                gt.push_back( new Rotation(angle) ) ;
            } else if ( transformation == "REF" ) {      // 鏡射
                istr >> angle ;
                gt.push_back( new Reflection(angle) ) ;
            }
                
        }

        // 清除旗幟
        istr.clear() ;
        
        // 列印
        cout << "  " << point << "  -->  " 
             << point.transformation(gt) << "\n\n" ;

        // 清除 gt 所指到所有轉換物件, 之後將 gt 向量陣列的長度
        // 調成零
        for ( i = 0 ; i < gt.size() ; ++i ) delete  gt[i] ;
        gt.resize(0)  ;
        
    } while ( no != 0 ) ;      // 如果沒有任何轉換動作則跳離迴圈

    return 0 ;
    
}

