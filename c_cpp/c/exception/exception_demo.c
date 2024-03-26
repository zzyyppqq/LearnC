//
// Created by 张宜鹏 on 2023/2/20.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <setjmp.h>

/**
1.使用标准C库提供了abort()和exit()两个函数，它们可以强行终止程序的运行，其声明处于<stdlib.h>头文件中。
2.使用assert(断言)宏调用，位于头文件<assert.h>中，当程序出错时，就会引发一个abort（）。
3.使用errno全局变量，由C运行时库函数提供，位于头文件<errno.h>中。
4.使用goto语句，当出错时跳转。
5.使用setjmp,longjmp进行异常处理。
 */

jmp_buf j;

void Exception(void) {
    longjmp(j, 1);
}

double diva(double num1, double num2)          // 两数相除函数
{
    double re;
    re = num1 / num2;
    return re;
}

int test_exit() {
    double a, b, result;
    printf(" 请输入第一个数字： ");
    scanf(" %lf ", &a);
    printf(" 请输入第二个数字： ");
    scanf(" %lf ", &b);
    if (0 == b)                                 // 如果除数为0终止程序
        exit(EXIT_FAILURE);
    result = diva(a, b);
    printf(" 相除的结果是: %.2lf\n ", result);
    return 0;
}

void Exception_Exit(void)    // 注册终止函数，通过挂接到此函数，捕获异常信息
{
    printf(" 试图去除以一个为0的数字，出现异常！\n ");
}

int test_atexit() {
    double a, b, result;
    printf(" 请输入第一个数字： ");
    scanf(" %lf ", &a);
    printf(" 请输入第二个数字： ");
    scanf(" %lf ", &b);
    if (0 == b)        // 如果除数为0终止程序 ,并挂接到模拟异常捕获的注册函数
    {
        atexit(Exception_Exit);
        exit(EXIT_FAILURE);
    }
    result = diva(a, b);
    printf(" 相除的结果是: %.2lf\n ", result);
    return 0;
}

int test_assert() {
    int a, b = 0;
    int result;
    printf(" 请输入第一个数字： ");
    scanf(" %lf ", &a);
    printf(" 请输入第二个数字： ");
    scanf(" %lf ", &b);
    assert(0 != b);                                 // 构造断言表达式，捕获预期异常错误
    result = diva(a, b);
    printf(" 相除的结果是: %.2lf\n ", result);
}

int test_goto() {
    int tag = 0;
    double a, b, result;
    if (1 == tag) {
        Throw:
        printf(" 除数为0，出现异常\n ");
    }
    tag = 1;
    printf(" 请输入第一个数字： ");
    scanf(" %lf ", &a);
    printf(" 请输入第二个数字： ");
    scanf(" %lf ", &b);
    if (b == 0)                                    // 捕获异常（或许这么说并不恰当，暂且这么理解）
        goto Throw;                                 // 抛出异常
    result = diva(a, b);
    printf(" %d\n ", errno);
    printf(" 相除的结果是: %.2lf\n ", result);

    return 0;
}


int test_setjmp_longjmp() {
    double a, b, result;


    printf(" 请输入第一个数字： ");
    scanf(" %lf ", &a);
    printf(" 请输入第二个数字： ");
    if (setjmp(j) == 0) {
        scanf(" %lf ", &b);
        if (0 == b)
            Exception();
        result = diva(a, b);
        printf(" 相除的结果是: %.2lf\n ", result);
    } else
        printf(" 试图除以一个为0的数字\n ");
    return 0;
}

int main() {
    test_goto();
    test_assert();

    return 0;
}
