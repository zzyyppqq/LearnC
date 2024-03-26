//
// Created by 张宜鹏 on 2022/9/18.
//

#include<iostream>

using namespace std;

int a = 10;
int b = 100;
int *q;

void func(int *p) {
    cout << "func:&p=" << &p << ",p=" << p << endl; //note:3
    p = &b;
    cout << "func:&p=" << &p << ",p=" << p << endl; //note:4
}
/**
 * 编译器总是要为函数的每个参数制作临时副本，指针参数p的副本是 p，
 * 编译器使 p = q(但是&p != &q,也就是他们并不在同一块内存地址，只是他们的内容一样，都是a的地址)。
 * 如果函数体内的程序修改了p的内容(比如在这里它指向b)。在本例中，p申请了新的内存，
 * 只是把 p所指的内存地址改变了(变成了b的地址,但是q指向的内存地址没有影响)，
 * 所以在这里并不影响函数外的指针q。
 * 这就需要二级指针操作
 */
int main() {
    cout << "&a=" << &a << ",&b=" << &b << ",&q=" << &q << endl; //note:1
    q = &a;
    cout << "*q=" << *q << ",q=" << q << ",&q=" << &q << endl; //note:2
    func(q);
    cout << "*q=" << *q << ",q=" << q << ",&q=" << &q << endl; //note:5
    return 0;
}

