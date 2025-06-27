Tutorial_1
// Tutorial 1: Introduction to C++ Multithreading
#include <iostream>
#include <thread>

void print_hello() {
    std::cout << "Hello from thread!" << std::endl;
}

int main() {
    std::thread t(print_hello);
    t.join();
    return 0;
}


// Tutorial 2: Basic Thread Synchronization

#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void print_hello() {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Hello from thread!" << std::endl;
    lock.unlock();
}

int main() {
    std::thread t1(print_hello);
    std::thread t2(print_hello);
    t1.join();
    t2.join();
    return 0;
}
