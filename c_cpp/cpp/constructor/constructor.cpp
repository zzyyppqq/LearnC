//
// Created by 张宜鹏 on 2023/1/31.
//

#include "constructor.h"

/// 单例
class Manager {
public:

    static Manager &getInstance();

    void print();

private:
    Manager();
    ~Manager();
    Manager(const Manager &instance);
    const Manager &operator=(const Manager &signal);
};

Manager &Manager::getInstance() {
    static Manager instance;
    return instance;
}

Manager::Manager()
{
    std::cout << "构造函数" << std::endl;
}

Manager::~Manager()
{
    std::cout << "析构函数" << std::endl;
}

void Manager::print()
{
    std::cout << "实例内存地址是:" << this << std::endl;
}


int main() {

    Manager &manager = Manager::getInstance();
    manager.print();

    return 0;
}
