//test.cpp
#include <stdio.h>
#include <iostream>

#include <thread>
#include <mutex>

std::mutex mMutex;

using namespace std;

static int count = 0;
static int MAX = 5000;
static int line = 0;
static int line_count = 5;

void thread1() {
    while (1) {
        if (count < MAX) {
            mMutex.lock();

            if (count < MAX) {
                std::cout << "A: " << ++count << "    ";

                if (++line == line_count) {
                    std::cout << endl;
                    line = 0;
                }
            } else {
                break;
            }

            mMutex.unlock();
        }
    }
}

void thread2() {
    while (1) {
        if (count < MAX) {
            mMutex.lock();

            if (count < MAX) {
                std::cout << "B: " << ++count << "    ";

                if (++line == line_count) {
                    std::cout << endl;
                    line = 0;
                }
            } else {
                break;
            }

            mMutex.unlock();
        }
    }
}

int main() {
    std::thread mThread1(thread1);
    std::thread mThread2(thread2);
    mThread1.detach();
    mThread2.detach();

    while (1) {
        int x;
        std::cin >> x;

        if (x == 0) {
            break;
        }
    }

    return 0;
}
