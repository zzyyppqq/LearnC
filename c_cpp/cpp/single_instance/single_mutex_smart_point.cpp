//
// Created by 张宜鹏 on 2023/1/31.
//

/// https://blog.csdn.net/unonoi/article/details/121138176
/// 方法1：返回智能指针
///  加锁的懒汉式实现  //

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
static std::mutex singletonMutex;

std::shared_ptr<Singleton> Singleton::getSingleton() {
    if (singleton == nullptr) {
        std::unique_lock<std::mutex> lock(singletonMutex);
        if (singleton == nullptr) {
            auto temp = std::shared_ptr<Singleton>(new Singleton());
            singleton = temp;
        }
    }
    return singleton;
}

int main() {
    std::shared_ptr<Singleton> instance = Singleton::getSingleton();
    instance->print();
    return 0;
}

