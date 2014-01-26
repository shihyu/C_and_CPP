// g++ -std=c++11  -Wl,--no-as-needed  test1.cpp  -pthread -o test1.out
#include <iostream>
#include <thread>

uint64_t get_thread_id() {
    static_assert(sizeof(std::thread::id) == sizeof(uint64_t), "this function only works if size of thead::id is equal to the size of uint_64");
    auto id = std::this_thread::get_id();
    uint64_t* ptr = (uint64_t*) &id;
    return (*ptr);
}

void test() {
    std::cout << "test" << std::endl;
    //std::cout << std::this_thread::get_id() << std::endl;
    std::cout << std::this_thread::get_id() << "  " << get_thread_id() << std::endl;
}

int main() {
    // std::cout << std::this_thread::get_id() << std::endl;
    std::cout << std::this_thread::get_id() << "  " << get_thread_id() << std::endl;
    std::thread t(test);
    t.join();
    return 0;
}
