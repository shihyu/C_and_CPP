#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using  namespace  std ;

typedef  int  Node ;

// 座標點類別
class  Point {

  private :
    
    double  x , y ;   // x , y 座標

  public :
    
    // 建構函式
    Point( double a = 0. , double b = 0. ) : x(a) , y(b) {}

    double  getx () const {  return x ;  }
    double  gety () const {  return y ;  }

    // 輸出運算子
    friend ostream& operator<< ( ostream& out , const Point& pt ) {
        out.setf(ios::fixed,ios::floatfield) ;
        out.precision(2) ;
        return  out << "(" << pt.x << "," << pt.y << ")" ;
    }

};

// 網格格子基礎類別
class  Geometrical_Cell {
    
  public :
    
    // 格子名稱
    virtual  string  cell_name() const = 0 ;
    
    // 格子頂點的編號
    virtual  void  get_nodes( Node node[] ) const = 0 ;

    // 格子的頂點數目
    virtual  int   node_no() const = 0 ;

    // 列印格子資料
    virtual  ostream&  print( ostream& out ) const = 0 ;

    // 複製格子
    virtual  Geometrical_Cell*  clone() const = 0 ;

    // 虛擬解構函式
    virtual  ~Geometrical_Cell() {}
    
} ;

// 覆載網格輸出運算子
ostream&  operator << ( ostream& out , 
                        const Geometrical_Cell& cell ) {
    return  cell.print( out ) ;
};
    

// 三角形格子
class  Triangular_Cell : public Geometrical_Cell {
    
  private :

    // 格子頂點編號
    Node     nodes[3] ;
    
  public :

    // 三個建構函式
    Triangular_Cell() {}

    Triangular_Cell( const Node& node1 , const Node& node2 , 
                     const Node& node3 ) {
        nodes[0] = node1 ;     nodes[1] = node2 ;
        nodes[2] = node3 ;
    }

    Triangular_Cell( const Node n[3] ) {
        for ( int i = 0 ; i < 3 ; ++i ) nodes[i] = n[i] ;
    }

    // 輸出格子頂點的編號
    void  get_nodes( Node  n[3] ) const {
        for ( int i = 0 ; i < 3 ; ++i ) n[i] = nodes[i] ;
    }

    // 回傳格子頂點數
    int   node_no() const {    return 3 ;    }

    // 格子名稱
    string  cell_name() const {  return  string("三角形格子") ;  }

    // 列印格子資料
    ostream&  print(ostream& out) const {
        return  out << "格子編號 : " << nodes[0] 
                    << " " << nodes[1] << " " << nodes[2] ;
    }

    // 複製格子
    Triangular_Cell*  clone() const { 
        return  new Triangular_Cell(nodes) ; 
    }

};

// 產生網格於區域 [0,1]x[0,1] 之內
class  Mesh_Generator {
    
  private :
  
    int                         division ;    // 切割等份
    vector<Point>               points   ;    // 頂點向量陣列
    vector<Geometrical_Cell*>   cells    ;    // 格子向量陣列

    // 清除網格 : 釋放動態格子記憶空間
    void  delete_mesh() {
        int i ;
        for ( i = 0 ; i < cells.size() ; ++i ) delete cells[i] ;
        cells.resize(0) ;
        points.resize(0) ;
    }
    
  public :
    
    // 預設建構函式
    Mesh_Generator( int d = 3 ) : division(d) {};
    
    // 複製建構函式
    Mesh_Generator( const Mesh_Generator& mesh ) {

        int i ;
        division = mesh.division ;

        for ( i = 0 ; i < mesh.points.size() ; ++i ) 
            points.push_back(mesh.points[i]) ;
        
        for ( i = 0 ; i < mesh.cells.size() ; ++i ) 
            cells.push_back( mesh.cells[i]->clone() ) ;

    }
    
    // 解構函式
    ~Mesh_Generator() {  delete_mesh() ;  }

    // 定義指定運算子
    Mesh_Generator&  operator = ( const Mesh_Generator& mesh ) {

        // 處理自我指定
        if ( this == &mesh ) return  *this ;

        int i ;

        // 去除已有的資料
        if ( cells.size() != 0 ) delete_mesh() ;
        
        // 設定新資料
        division = mesh.division ;

        for ( i = 0 ; i < mesh.points.size() ; ++i ) 
            points.push_back(mesh.points[i]) ;
        
        for ( i = 0 ; i < mesh.cells.size() ; ++i ) 
            cells.push_back( mesh.cells[i]->clone() ) ;

        return  *this ;

    }

    // 設定與取得切割區域
    void  set_division( int d ) {  division = d ;         }
    int   get_division() const { return  division  ; }
    
    // 產生三角形網格
    void  generate_triangular_mesh() {

        int    i , j , c1 , c2 , c3 , c4 ;
        int    line_point_no = division+1 ;
        double  ds =  1. / division ;

        if ( cells.size() != 0 )  delete_mesh() ;
        
        // 儲存格子點編號
        for ( j = 0 ; j < line_point_no ; ++j ) {
            for ( i = 0 ; i < line_point_no ; ++i ) {
                points.push_back( Point( i * ds , j * ds ) ) ;
            }
        }

        // 儲存三角形格子
        for ( j = 0 ; j < division ; ++j ) {
            for ( i = 0 ; i < division ; ++i ) {
                c1 = i  + j * line_point_no ;
                c2 = c1 + 1 ;
                c3 = c2 + line_point_no ;
                c4 = c1 + line_point_no ;
                cells.push_back( new Triangular_Cell(c1,c2,c4) ) ;
                cells.push_back( new Triangular_Cell(c2,c3,c4) ) ;
            }
        }
        
    }

    // 使用 gnuplot 的格式輸出網格資料
    void  output_mesh( const string&  filename = "mesh" ) const {

        int       i , j ;
        Node      nodes[4] ;
        ofstream  fout( filename.c_str() , ios::out ) ;
        
        fout.setf(ios::fixed,ios::floatfield) ;
        fout.precision(3) ;
        
        for ( i  = 0 ; i < cells.size() ; ++i ) {

            cells[i]->get_nodes(nodes) ;

            fout << "# " << i << " : " << cells[i]->cell_name() 
                 << " --- " ;

            for ( j = 0 ; j < cells[i]->node_no() ; ++j ) 
                fout << setw(3) << nodes[j] << " " ;
            fout << endl ;
            
            for ( j = 0 ; j < cells[i]->node_no() ; ++j ) {
                fout << setw(5) << points[nodes[j]].getx() 
                     << " " << setw(5) << points[nodes[j]].gety() 
                     << "\n" ;
            }
            fout << setw(5) << points[nodes[0]].getx() 
                 << " " << setw(5) << points[nodes[0]].gety() 
                 << "\n\n" ;
        }

        fout.close() ;

    }
    

    // 覆載輸出運算子
    friend  ostream& operator << ( ostream& out , 
                                   const Mesh_Generator& mesh ) {

        int    i , j ;
        Node   nodes[4]  ;
        
        out << "> 網格總共有 " << mesh.cells.size() << " 格子與 " 
            << mesh.points.size() << " 格子點" << "\n\n" ;
        
        for ( i  = 0 ; i < mesh.cells.size() ; ++i ) {

            mesh.cells[i]->get_nodes(nodes) ;
            out << mesh.cells[i]->cell_name() << " : "  
                << i << "\n" ;

            for ( j = 0 ; j < mesh.cells[i]->node_no() ; ++j ) {
                out << "[" << setw(2) << nodes[j] << "] : " 
                    << mesh.points[nodes[j]] << "   " ;
            }
            out << "\n\n" ;

        }

        return out ;
        
    }
    
};

int  main() {

    // 產生網格, 每一邊切成兩等份
    Mesh_Generator  mesh(2) ;

    // 產生三角形網格
    mesh.generate_triangular_mesh() ;

    // 輸出網格資料
    cout << mesh << endl ;

    // 將網格資料輸出成 gnuplot 格式檔
    mesh.output_mesh() ;

    return 0 ;
    
}
