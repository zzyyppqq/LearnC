//
// Created by 张宜鹏 on 2022/4/19.
//

#include <iostream>

using namespace std;

class Box {
public:
    Box() {
        cout << "调用构造函数！" << endl;
    }

    ~Box() {
        cout << "调用析构函数！" << endl;
    }
};

int main() {
    /**
     * malloc() 函数在 C 语言中就出现了，在 C++ 中仍然存在，但建议尽量不要使用 malloc() 函数。
     * new 与 malloc() 函数相比，其主要的优点是，new 不只是分配了内存，它还创建了对象。
     * 在任何时候，当您觉得某个已经动态分配内存的变量不再需要使用时，
     * 您可以使用 delete 操作符释放它所占用的内存
     */
    double *pvalue = NULL; // 初始化为 null 的指针
    pvalue = new double;   // 为变量请求内存

    *pvalue = 29494.99;     // 在分配的地址存储值
    cout << "Value of pvalue : " << *pvalue << endl;

    delete pvalue;         // 释放内存

    // 动态分配,数组长度为 m
    int *array = new int[10];

    //释放内存
    delete[] array;

    Box* myBoxArray = new Box[4];

    delete [] myBoxArray; // 删除数组

    // new创建类对象，使用完后需使用delete删除，跟申请内存类似。
    Box * box = new Box();
    delete box;

    return 0;
}

