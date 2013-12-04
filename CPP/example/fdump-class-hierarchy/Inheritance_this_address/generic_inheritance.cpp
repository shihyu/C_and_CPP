#include <iostream>
using namespace std;

class CBaseA {
public:
    void test3() {}
    char m_A[32];

    void test1() {}
    void test2() {}
    CBaseA() {
        cout << "CBaseA this address=" << this << endl;
    }
};

class CBaseB : public CBaseA {
public:
    char m_B[64];
    void test() {}

    CBaseB() {
        cout << "CBaseB this address=" << this << endl;
    }
};

class CDerive : public CBaseB {
public:
    char m_D[128];

    CDerive() {
        cout << "CDerive this address=" << this << endl;
    }
};

int main() {
    CDerive* pD = new CDerive;
}
