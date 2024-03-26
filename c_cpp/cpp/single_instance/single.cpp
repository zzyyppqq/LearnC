//
// Created by 张宜鹏 on 2023/1/31.
//

#include <iostream>
/// 静态局部变量的懒汉单例（C++11线程安全）
///  内部静态变量的懒汉实现  //

class Single {

public:
    // 获取单实例对象
    static Single &GetInstance();

    static Single *GetInstance2();

    // 打印实例地址
    void Print();

private:
    // 禁止外部构造
    Single();

    // 禁止外部析构
    ~Single();

    // 禁止外部拷贝构造
    Single(const Single &signal);

    // 禁止外部赋值操作
    const Single &operator=(const Single &signal);
};


Single &Single::GetInstance() {
    /**
     * 局部静态特性的方式实现单实例。
     * 静态局部变量只在当前函数内有效，其他函数无法访问。
     * 静态局部变量只在第一次被调用的时候初始化，也存储在静态存储区，生命周期从第一次被初始化起至程序结束止。
     */
    static Single signal;
    return signal;
}

Single *Single::GetInstance2() {
    static Single signal;
    return &signal;
}

void Single::Print() {
    std::cout << "我的实例内存地址是:" << this << std::endl;
}

Single::Single() {
    std::cout << "构造函数" << std::endl;
}

Single::~Single() {
    std::cout << "析构函数" << std::endl;
}

void test() {
}

int main() {

    Single::GetInstance().Print();
    Single::GetInstance().Print();
    Single::GetInstance().Print();

    Single::GetInstance2()->Print();
    Single::GetInstance2()->Print();
    Single::GetInstance2()->Print();


    return 0;
}