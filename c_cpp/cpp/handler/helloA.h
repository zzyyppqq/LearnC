//
// Created by zhangyipeng on 2023/8/9.
//

#ifndef CPPSTUDY_HELLOA_H
#define CPPSTUDY_HELLOA_H

#include <stdio.h>

#pragma once

class helloA {
public:
    helloA(void);
    ~helloA(void);
    virtual void func() const { printf("A"); }
    virtual helloA* clone() const {return new helloA(*this);}
};

helloA::helloA() {}
helloA::~helloA() {}

#endif //CPPSTUDY_HELLOA_H
