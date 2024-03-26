//
// Created by zhangyipeng on 2023/8/9.
//

#ifndef CPPSTUDY_MYSAMPLE_H
#define CPPSTUDY_MYSAMPLE_H

#pragma once

#include "helloA.h"
#include "helloB.h"
#include <stddef.h>

class mysample {
public:

    mysample() : p(0), use(1) {};

    mysample(const helloA &a) : p(a.clone()), use(1) {};

    mysample(const mysample &i) : p(i.p), use(i.use) { use++; }

    ~mysample() { decr_use(); };

    mysample &operator=(const mysample &i) {
        use++;
        decr_use();
        p = i.p;
        use = i.use;
        return *this;
    }

    const helloA *operator->() const { if (p)return p; }

    const helloA &operator*() const { if (p)return *p; }

private:
    helloA *p;
    size_t use;

    void decr_use() { if (-use == 0)delete p; }
};

#endif //CPPSTUDY_MYSAMPLE_H
