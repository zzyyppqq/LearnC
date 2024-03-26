//
// Created by 张宜鹏 on 2022/11/2.
//

#include <stdio.h>
#include<stdarg.h>

/**
 * C语言函数中“…”参数的含义。与它相关还涉及到以下4个部分：
 *（1）va_list变量
 *（2）va_start()
 *（3）va_arg()
 *（4）va_end()
 * va_list是一个指向函数的参数的指针。
 * va_start()用于初始化va_list变量。
 * va_arg()用于返回可变参数。
 * va_end()用于结束可变参数的获取
 */
void fun(int a, ...) {
    va_list pp;
    va_start(pp, a);
    do {
        printf("param =%d\n", a);
        a = va_arg(pp, int);//使 pp 指向下一个参数，将下一个参数的值赋给变量 a
    } while (a != 0);//直到参数为 0 时停止循环
}

int main() {
    fun(20, 40, 60, 80, 0);
}