//
// Created by 张宜鹏 on 2023/1/31.
//

// 饿汉实现 //
// 使用 C++11 std::call_once 实现单例（C++11线程安全）

#include <iostream>
#include <memory>
#include <mutex>

class Singleton {
public:
    static std::shared_ptr<Singleton> getSingleton();

    void print() {
        std::cout << "Hello World." << std::endl;
    }

    ~Singleton() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

private:
    Singleton() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

static std::shared_ptr<Singleton> singleton = nullptr;
static std::once_flag singletonFlag;

std::shared_ptr<Singleton> Singleton::getSingleton() {
    std::call_once(singletonFlag, [&] {
        singleton = std::shared_ptr<Singleton>(new Singleton());
    });
    return singleton;
}


int main() {
    std::shared_ptr<Singleton> single = Singleton::getSingleton();
    single->print();

    return 0;
}