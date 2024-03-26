//
// Created by zhangyipeng on 2023/8/9.
//

#ifndef CPPSTUDY_HELLOB_H
#define CPPSTUDY_HELLOB_H

#include <stdio.h>

#pragma once

#include "helloA.h"

class helloB : public helloA {
public:
    helloB(void);
    ~helloB(void);

    void func() const { printf("B"); }
    virtual helloB* clone() const{return new helloB(*this);}
};


helloB::helloB() {}
helloB::~helloB() {}


#endif //CPPSTUDY_HELLOB_H
