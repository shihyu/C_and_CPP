#ifndef _MSC_VER
#undef NULL
#define NULL 0
#endif
#include <iostream>
#include <cstdlib>
#define BUFFER_SIZE 7

using namespace std;

class ClassA {
public:
    // 三種建構子
    ClassA() {
        cout << "ClassA():" << endl;
        this->setAlloc(BUFFER_SIZE);
        this->setData();
    }
    ClassA(const int n) {
        cout << "ClassA(const int n):" << endl;
        this->setAlloc(n);
        this->setData();
    }
    // 複製建構子
    ClassA(const ClassA& clone) {
        cout << "ClassA(const ClassA& clone):" << endl;
        this->setAlloc(clone.m_N);
        this->setData(clone.m_pn);
    }
    // 複製指定運算子成員函式
    ClassA& operator=(const ClassA& clone) {
        cout << "ClassA& operator=(const ClassA& clone)" << endl;

        // 保護：禁止自己設值給自己
        if (this != &clone) {
            this->setData(clone.m_pn);
        }

        return *this;
    }
    // 解構子
    ~ClassA() {
        cout << "~Destructor!!!" << endl;
        // 釋放記憶體
        delete [] this->m_pn;
    }
    // 配置
    void setAlloc(const int n) {
        this->m_N = n;
        // 配置一塊記憶體給指標
        this->m_pn = new int[this->m_N];
    }
    // 填入一堆的整數值
    void setData(int* pn = NULL) {
        for (int i = 0; i < this->m_N; i ++) {
            // 給初始值
            if (pn == NULL) {
                this->m_pn[i] = (2 * i + 1);
            }
            // 複製指標儲存的整數值
            else {
                this->m_pn[i] = pn[i];
            }
        }
    }
    // 列印顯示
    void print(void) {
        for (int i = 0; i < this->m_N; i ++) {
            cout << " " << this->m_pn[i];
        }

        cout << endl;
    }
private:
    // 指標
    int* m_pn;
    // 元素個數
    int m_N;
};



int
main(int argc, char** argv) {
    // 建立第一個物件
    ClassA A(BUFFER_SIZE);
    // 開始執行 ClassA(const ClassA& clone)
    ClassA B = A;
    ClassA C;
    // 開始執行 ClassA& operator=(const ClassA& clone)
    C = A;
    
    cout << "classA D +" << endl;
    ClassA D = ClassA(BUFFER_SIZE);

    return 0;
}
