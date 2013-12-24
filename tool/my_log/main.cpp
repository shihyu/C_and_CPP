#include <iostream>
#include "tracer.h"

using namespace std;
#define LOG_TAG "main"

class B {
public:
    void test() {
        GLOGENTRY();
    }
};

int main(int argc, char* argv[]) {
    GLOGENTRY();
    B b;
    b.test();
    return 0;
}
