// g++ -std=c++11  -Wl,--no-as-needed  test1.cpp  -pthread -o test1.out
#include <iostream>
#include <thread>

void test() {
    std::cout << "test" << std::endl;
}

int main() {
    std::thread t(test);
    t.join();
    return 0;
}
