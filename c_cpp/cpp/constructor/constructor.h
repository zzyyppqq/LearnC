//
// Created by 张宜鹏 on 2023/1/31.
//

#ifndef CPP_CONSTRUCTOR_H
#define CPP_CONSTRUCTOR_H

#include <iostream>

class Uncopyable
{
protected:
    Uncopyable() {} // 允许derived对象构造和析构
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable &); // 阻止copying
    Uncopyable &operator=(const Uncopyable &);
};

class Node : private Uncopyable
{
public:
    Node(int _data = 0) : data(_data) {}
    int get() const { return data; }
    void set(int _data) { data = _data; }

private:
    int data;
};


class Complex{
public:
    Complex() {}

    double real, imag;
    Complex(double r,double i){
        real = r; imag = i;
    }
    Complex(double r): real(r) {} // //参数可以有默认值（默认值不是构造函数特有）
    // 复制构造函数 的复写
    Complex(const Complex & c){
        real = c.real; imag = c.imag;
        std::cout<<"Copy Constructor called"<< std::endl ;
    }
};

/**
 * 复制构造函数
 */
void testCopy() {
    Node node;
//    Node node1(node);
//    Node node2 = node;


    Complex c;
    Complex c2(c);
}


// 在C++类中，编译器可以暗自为class创建default构造函数、copy构造函数、copy assignment操作符，以及析构函数
template<class T>
class NamedObject {
public:

    NamedObject() {

    }

    NamedObject(std::string& nameVal, const T objectVal)
            :nameVal(nameVal),objectVal(objectVal)
    {}


    void show() {
        std::cout << nameVal << "\t" << objectVal << std::endl;
    }

    NamedObject(const NamedObject&);
    NamedObject& operator=(const NamedObject&) = default;

private:
//    string&和const在阻止赋值动作的发生
//    std::string& nameVal;
//    const T objectVal;
    std::string nameVal;
    T objectVal;
};

/**
 * Copy Assignment操作符赋值
 */
void testCopyAssignment() {
    std::string newDog = "PersonPhone";
    std::string oldDog = "Person";

    NamedObject<int> p(newDog, 2);
    NamedObject<int> s(oldDog, 1);

    p = s;
}

#endif //CPP_CONSTRUCTOR_H
