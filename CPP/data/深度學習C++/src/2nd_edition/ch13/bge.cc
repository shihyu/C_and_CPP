#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using  namespace  std ;

// 將前一範例相關程式碼加入本程式使用
#include "transformation.h"   

// 基本幾何圖形
class  Basic_Geometric_Entity {

    public :

        // (1) 幾何轉換 : 用來平移, 旋轉, 鏡射等等
        virtual Basic_Geometric_Entity*  transformation( 
                 const vector<GT*>& geotrs ) const = 0 ;

        // (2) 複製物件
        virtual Basic_Geometric_Entity* clone() const = 0 ;

        // (3) 列印物件
        virtual ostream& print(ostream& out) const = 0 ;

        // (4) 虛擬解構函式
        virtual  ~Basic_Geometric_Entity() {}

        // (5) 覆載輸出運算子
        friend  ostream&  operator<< ( 
            ostream& out , const Basic_Geometric_Entity& bge ) {
             return  bge.print(out) ;
        }

} ;


// 線段類別
class  Line : public  Basic_Geometric_Entity {

  private :

    Point  p , q ;   // 線段的兩個端點

  public :
 
    // 建構函式
    Line( const Point& a , const Point& b ) : p(a) , q(b) {}

    // 搬動線段
    virtual Line*  transformation( 
        const vector<GT*>& geotrs ) const {
        return  new  Line( p.transformation(geotrs),
                           q.transformation(geotrs)) ;
    }

    // 複製物件, 並回傳其指標
    virtual  Line*  clone() const { return  new  Line(*this) ; }

    // 列印線段
    virtual  ostream&  print( ostream& out ) const {
        return  out << "> Line : " << p << " --> " << q  ;
    } 

} ;   


// 圓
class  Circle : public  Basic_Geometric_Entity {
    
  private :
    
    Point    center ;   // 圓心
    Length   radius ;   // 半徑
    
  public :

    // 建構函式
    Circle( const Point& c , Length r ) : center(c) , radius(r) {}

    // 搬動圓
    virtual  Circle*  transformation( 
        const vector<GT*>& geotrs ) const {
        return new Circle(center.transformation(geotrs),radius) ;
    }

    // 複製物件, 並回傳其指標
    virtual  Circle* clone() const { return new Circle(*this) ; }

    // 列印圓
    virtual  ostream&  print( ostream& out ) const {
        return  out << "> Circle : center = " 
                    <<  center << " , radius = " << radius  ;
    } 

} ;   
    

typedef  Basic_Geometric_Entity  BGE ;

int main() {
    
    int  i ;

    // 產生兩個向量陣列用來儲存幾何類別架構內動態物件的指標
    vector<BGE*>  bge1 , bge2 ;

    // 動態產生三個幾何物件

    // (1) 圓 : 圓心 (1,1) 半徑 1 
    bge1.push_back( new Circle(Point(1,1),1) ) ;         

    // (2) 直線 : 兩端點 (1,1) (2,1) 
    bge1.push_back( new Line(Point(1,1),Point(2,1)) ) ;  

    // (3) 圓 : 圓心 (1,0) 半徑 3
    bge1.push_back( new Circle(Point(1,0),3) ) ;         

    // 列印所有的幾何物件
    cout << "搬動前的圖形" << endl ;
    for ( i = 0 ; i < bge1.size() ; ++i ) 
        cout << *bge1[i] << endl ;

    cout << endl ;

    // 儲存幾何轉換資料
    vector<GT*> gt ;

    // 搬動幾何圖形, 先逆時針旋轉 90 度, 對 45 度直線作鏡射, 
    // 再往右移 1 單位
    gt.push_back( new Rotation(90) ) ;
    gt.push_back( new Reflection(45) ) ;
    gt.push_back( new Translation(1,0) ) ;
    
    // 產生搬動後的圖形
    for ( i = 0 ; i < bge1.size() ; ++i ) 
        bge2.push_back( bge1[i]->transformation( gt ) ) ;

    // 列印搬動後的所有幾何圖形
    cout << "搬動後的圖形 : " 
         << "(1) 逆時針旋轉 90 度 (2) 45 度線鏡射 (3) 右移 1"
         << endl ;

    for ( i = 0 ; i < bge2.size() ; ++i ) 
        cout << *bge2[i] << endl ;

    cout << endl ;

    // 複製 bge2 幾何圖形
    vector<BGE*>  bge3 ;
    for ( i = 0 ; i < bge2.size() ; ++i ) {
        bge3.push_back( bge2[i]->clone() ) ;
    }

    cout << "複製圖形" << endl ;
    for ( i = 0 ; i < bge3.size() ; ++i ) 
        cout << *bge3[i] << endl ;
    
    
    // 刪除所有的動態物件
    for ( i = 0 ; i < bge1.size() ; ++i ) {
        delete  bge1[i] ;        
        delete  bge2[i] ;
        delete  bge3[i] ;
    }
    
    // 刪除所有的動態物件
    for ( i = 0 ; i < gt.size() ; ++i )  delete gt[i] ;

    return 0 ;
    
}
