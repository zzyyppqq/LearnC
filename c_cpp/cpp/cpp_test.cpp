//
// Created by 张宜鹏 on 2022/4/28.
//

#include "stdio.h"

int main(int argc, char **argv) {

    int i = 10;
    int *p = &i;
    int &r = i;// c++支持
    int *p1 = &r;
//    int &b=10;//error

    printf("指针（地址）的值为p(16进制地址)：%p\n", p);
    printf("指针（地址）的值为p(long)：%lld\n", p);
    printf("指针（地址）的值为&i(16进制地址)：%p\n", &i);
    printf("指针（地址）的值为&i(long)：%lld\n", &i);
    printf("指针（地址）的值为*p：%d\n", *p);
    printf("变量的值为：%d\n", i);

    printf("指针（地址）的值为&r(16进制地址)：%p\n", &r);
    printf("指针（地址）的值为&r(long)：%lld\n", &r);

    printf("指针（地址）的值为p1(16进制地址)：%p\n", p1);
    printf("指针（地址）的值为p1(long)：%lld\n", p1);

    int j = 20;
    int *****pp;

    int x = 10, y = 20, z = 30;
    int *pi = &x; //pi中存储了的地址，即，指向了x，*pi就是x
    int &ri = x; //ri是的一个别名，从现在起ri就捆绑到了x上, ri就是x
    printf("x=%d y=%d z=%d\n\n", x, y, z);
    printf("before assignment ri=%d x=%d\n", ri, x);
    ri = z; //导致×值变成30
    printf("after assignment ri=%d x=%d\n\n", ri, x);
    printf("before change pi=%d=%d\n", *pi, x);
    pi = &y; //pi指向y
    printf("pi change to y pi=%d y=%d\n", *pi, y);
    *pi = z; //导致y变成了30
    printf("after assignment pi=%d y=%d\n", *pi, y);
}