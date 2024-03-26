//
// Created by 张宜鹏 on 2022/4/19.
//

#include <stdio.h>

// 预处理器实例
#define MAX_ARRAY_LENGTH 20
// 预处理器运算符
#define message_for(a, b) printf(#a " and " #b ": We love you!\n")
// 标记粘贴运算符（##）
#define tokenpaster(n) printf ("token" #n " = %d", token##n)

#if !defined (MESSAGE)
#define MESSAGE "You wish!"
#endif

// 参数化的宏
#define square(x) ((x) * (x))
#define MAX(x,y) ((x) > (y) ? (x) : (y))

#define CONNECT(a,b) a##b
//#define TOCHAR(a) #@a
#define TOSTRING(a) #a

#define INCLUDE_MY_MATH
#include "test.h"

int main()
{
    // 预定义宏
    printf("File :%s\n", __FILE__ );
    printf("Date :%s\n", __DATE__ );
    printf("Time :%s\n", __TIME__ );
    printf("Line :%d\n", __LINE__ );
    printf("ANSI :%d\n", __STDC__ );

    message_for(Carole, Debra);
    int token34 = 40;
    tokenpaster(34);

    printf("Here is the message: %s\n", MESSAGE);

    //a##b表示连接
    int n = CONNECT(123, 456);                //结果  n = 123456
//    char *str = CONNECT("abcd", "efg");       //结果  str = "abcdefg"

//@#a 表示用单引号包括参数a，返回的是一个字符
//    char * ch1 = TOCHAR(1);        //结果  ch = '1'
//    char * ch2 = TOCHAR(123);      //报错，单引号只用在单个字符里

//#a 表示用双引号包括参数a，返回一个字符串
    char * str1 = TOSTRING(123);    // str = "123"
    return 0;
}