//
// Created by 张宜鹏 on 2023/2/2.
//

/// 我们知道在C++中指针也是一种变量类型，其中存储的是地址。
/// 我们知道C++中函数参数的传递默认是值传递，如果我想在一个函数中修改变量的值，当退出函数的时候这种影响保留的话，就需要使用变量的指针或者应用作为参数。
/// 同样指针作为一种变量，在传递参数的时候，指针也是按照值传递的，这样就会导致一个问题，当我们使用值传递的时候，如果我们在函数中修改了指针变量的指向，
/// 当函数退出时这种影响不会保留。如果我们想在一个函数中修改指针的指向，并且在退出函数后这种影响保留，就需要使用指针变量的指针或者引用传递参数。

#include <iostream>

using namespace std;
struct point {
    int x;
    int y;
};

void changenum1(point *&pnum) { //point *&pnum表示指向point类型的指针的引用，即point*类型变量的引用
    pnum = new point;
    pnum->x = 4;
}

void changenum2(point *pnum) {
    pnum = new point;
    pnum->x = 4;
}


void test1() {
    point *num = new point;
    num->x = 10;
    changenum1(num);
    std::cout << "指针引用" << num->x << endl;
}

void test2() {
    point *num = new point;
    num->x = 10;
    changenum2(num);
    std::cout << "指针" << num->x << endl;
}

int main() {
    cout << "开始执行程序" << endl;
    test1();
    test2();
    cout << "执行程序完毕" << endl;
    return 0;
}
