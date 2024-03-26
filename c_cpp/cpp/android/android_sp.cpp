//
// Created by 张宜鹏 on 2022/5/19.
//

#include <stdio.h>
#include "RefBase.h"
#include "StrongPointer.h"

using namespace android;

class Demo: public RefBase {

};

class Point: public LightRefBase<Point> {
public:
    Point() {
        printf("Point()\n");
    }
    ~Point() {
        printf("~Point()\n");
    }
    void print() {
        printf("print()\n");
    }
};

int main() {
    int mCount = 0;
    __sync_fetch_and_add(&mCount, 1);
    __sync_fetch_and_add(&mCount, 1);
    __sync_fetch_and_add(&mCount, 1);
    printf("mCount: %d\n", mCount);


//    sp<Demo> sp_demo = new Demo();
//    sp_demo.get();

    sp<Point> point = new Point();
    Point *pPoint = point.get();
    pPoint->print();

    return 1;
}
