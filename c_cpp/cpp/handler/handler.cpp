//
// Created by zhangyipeng on 2023/8/9.
//

#include "helloA.h"
#include "helloB.h"
#include "mysample.h"
#include <vector>
#include <list>

using namespace std;

void printVector(vector<helloA> &vec) {
    for (vector<helloA>::iterator iter = vec.begin(); iter != vec.end(); iter++) {
        (*iter).func();
    }
}


void printVectorPoint(vector<helloA *> &vec) {
    for (vector<helloA *>::iterator iter = vec.begin(); iter != vec.end(); iter++) {
        (*iter)->func();
    }
}

void test1() {
    vector<helloA> vec;
    helloA a;
    helloB b;
    vec.push_back(a);
    vec.push_back(b);// 将b转化为了它的基类helloA.

    printVector(vec); // AA
}

// 用指针代替对象方法：如：vector<helloA*>vec;这样做可以达到多态的目的，但程序员必须接管内存管理
// 但问题来了，这里假如vec的生命周期结束了，vec不会主动释放b所占用的内存，如果不手动delete b,就会产生内存泄漏。
// 接下来，就实现下句柄类，来解决如上问题。
void test2() {
    vector<helloA *> vec;
    helloA *a = new helloA;
    helloB *b = new helloB;
    vec.push_back(a);
    vec.push_back(b);

    printVectorPoint(vec);// AB
}

void test3() {
    vector<mysample> vec;
    helloA a;
    helloB b;

    // 类似shared_ptr，我们引入了计数，在vec生命周期结束时，我们不需要自己释放内存
    mysample sample1(a);
    mysample sample2(b);

    vec.push_back(sample1);
    vec.push_back(sample2);


    for (vector<mysample>::iterator iter=vec.begin(); iter != vec.end(); iter++)
    {
        (*iter)->func();
    }

}

int main() {

    test1();
    printf("\n");
    test2();
    printf("\n");
    test3();
    printf("\n");

    return 0;
}