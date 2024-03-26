//
// Created by 张宜鹏 on 2022/6/20.
// https://zhuanlan.zhihu.com/p/372557271
//

#include <cstdio>

//构造3个通用函数
void TEST1(void) { printf("test1\n"); }//函数定义
void TEST2(void) { printf("test2\n"); }//函数定义
void TEST3(void) { printf("test3\n"); }//函数定义

//声明
typedef void (*func)(void);


void test(int i) {
    func vTask[3] = {&TEST1, &TEST2, &TEST3};
    func fun = vTask[i];
    (*fun)();
}

int main() {
    test(0);
    test(1);
    test(2);
    return 0;
}