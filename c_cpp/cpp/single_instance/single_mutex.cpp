//
// Created by 张宜鹏 on 2023/1/31.
//

/// https://blog.csdn.net/unonoi/article/details/121138176
/// 方法1：返回普通指针
///  加锁的懒汉式实现  //

#include <iostream>

class SingleInstance {

public:
    // 获取单实例对象
    static SingleInstance *&GetInstance();
    static SingleInstance *GetInstance2();

    //释放单实例，进程退出时调用
    static void deleteInstance();
    
    int x = 10;

    // 打印实例地址
    void Print();

private:
    // 将其构造和析构成为私有的, 禁止外部构造和析构
    SingleInstance();

    ~SingleInstance();

    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    SingleInstance(const SingleInstance &signal);

    const SingleInstance &operator=(const SingleInstance &signal);

private:
    // 唯一单实例对象指针
    static SingleInstance *m_SingleInstance;
    static std::mutex m_Mutex;
};


//初始化静态成员变量
SingleInstance *SingleInstance::m_SingleInstance = nullptr;
std::mutex SingleInstance::m_Mutex;

// 注意：返回的是指针的引用
SingleInstance *&SingleInstance::GetInstance() {

    //  这里使用了两个 if 判断语句的技术称为双检锁；好处是，只有判断指针为空的时候才加锁，
    //  避免每次调用 GetInstance的方法都加锁，锁的开销毕竟还是有点大的。
    if (m_SingleInstance == nullptr) {
        std::unique_lock<std::mutex> lock(m_Mutex); // 加锁
        if (m_SingleInstance == nullptr) {
            m_SingleInstance = new(std::nothrow) SingleInstance();
        }
    }

    return m_SingleInstance;
}

// 注意：返回的是指针
SingleInstance *SingleInstance::GetInstance2() {

    //  这里使用了两个 if 判断语句的技术称为双检锁；好处是，只有判断指针为空的时候才加锁，
    //  避免每次调用 GetInstance的方法都加锁，锁的开销毕竟还是有点大的。
    if (m_SingleInstance == nullptr) {
        std::unique_lock<std::mutex> lock(m_Mutex); // 加锁
        if (m_SingleInstance == nullptr) {
            m_SingleInstance = new(std::nothrow) SingleInstance();
        }
    }

    return m_SingleInstance;
}

void SingleInstance::deleteInstance() {
    std::unique_lock<std::mutex> lock(m_Mutex); // 加锁
    if (m_SingleInstance) {
        delete m_SingleInstance;
        m_SingleInstance = nullptr;
    }
}

void SingleInstance::Print() {
    std::cout << "我的实例内存地址是:" << this << std::endl;
    std::cout << "x:" << x << std::endl;
}

SingleInstance::SingleInstance() {
    std::cout << "构造函数" << std::endl;
}

SingleInstance::~SingleInstance() {
    std::cout << "析构函数" << std::endl;
}

int main() {
    SingleInstance *&pSingleInstance = SingleInstance::GetInstance();
    pSingleInstance->x = 5;
    pSingleInstance->Print();

    SingleInstance *pInstance = SingleInstance::GetInstance2();
    pInstance->x = 20;
    pInstance->Print();



    return 0;
}

