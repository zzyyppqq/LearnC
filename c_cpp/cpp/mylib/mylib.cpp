//
// Created by 张宜鹏 on 2022/4/28.
//

#include "mylib.h"


#include <iostream>


using namespace std;

void MyNumber::setNumber(int a, int b) {
    this->a = a;
    this->b = b;
}

void MyNumber::printMsg() {
    std::cout << "a+b=" << a+b << std::endl;
}