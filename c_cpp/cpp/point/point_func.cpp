//
// Created by 张宜鹏 on 2022/9/18.
//

#include<iostream>

using namespace std;

void change(int *tmp_t) {
    *tmp_t = 1;
    return;
}

void change_2(int &tmp_t) {
    tmp_t = 2;
    return;
}

/**
 * 对于定义的int **buf_t中，二级指针buf_t=&buf,指向为buf(还是一个指针)，
 * 一级指针*buf_t=buf，指向为*buf，值**buf_t= *buf
 */
int mem_init(int **buf_t) {
    *buf_t = (int *) malloc(100);
    return 1;
}

int mem_init_2(int *&buf_t) {
    buf_t = (int *) malloc(200);
    return 1;
}

// 要定义的类型是void (*)(int)，即参数一个int，什么也不返回的函数指针，定义的别名是p。
typedef char (*p)(int);
p pFun;
char glFun(int a){ return 'c';}

/**
 * C语言中函数传递参数都是传递"值"的
 * 1.因为我们传递的是“值”，如果你想在函数change()中修改这个tmp的值能在fun()中生效的话，那么就需要用指针来传递
 * 2.我们通过传递指针来达到修改一个值的目的，那么当你需要修改一个指针的时候呢，这个时候我们就需要指针的指针了(二级指针)
 *
 */
int main() {
    pFun = glFun;
    (*pFun)(2);


    int tmp = 0;
    change(&tmp);
    printf("################ tmp = %d \n", tmp);

    change_2(tmp);
    printf("################ tmp = %d \n", tmp);

    // 通过调用men_init()函数来实现给buf分配内存空间的目的。
    // 首先buf是我们定义的一个指 针，&buf则是指向buf的指针(二级指针)
    // 我们通过把&buf传递个men_init()函数，那么此时二级指针buf_t = &buf
    // 所以说buf_t是指向buf的指针
    // 那么对于*buf_t的操作其实就是对buf的操作
    int *buf;
    cout << "buf = " << buf << endl;
    mem_init(&buf);
    cout << "buf = " << buf << endl;
    int *buf2;
    cout << "buf2 = " << buf2 << endl;
    mem_init_2(buf2);
    cout << "buf2 = " << buf2 << endl;
    return 0;
}

