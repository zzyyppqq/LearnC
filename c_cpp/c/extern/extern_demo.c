//
// Created by 张宜鹏 on 2022/11/3.
//
//一、引用同一个文件中的变量
//二、引用另一个文件中的变量
//三、引用另一个文件中的函数

#include<stdio.h>

int func();

int main() {
    func(); //1
    // 引用同一个文件中的变量
    extern int num;
    printf("num: %d\n", num); //不声明无法访问
    // 引用另一个文件中的变量(不可变)
    extern const int num_lib;
    printf("num_lib: %d\n", num_lib);
    // 引用另一个文件中的变量(可变)
    extern int num_lib_var;
    printf("num_lib_var: %d\n", num_lib_var);
    num_lib_var = 10;
    printf("num_lib_var: %d\n", num_lib_var);
    // 引用另一个文件中的函数
    extern void func_lib();
    func_lib();

    return 0;
}

int num = 3;

int func() {
    printf("func num: %d\n", num);
}