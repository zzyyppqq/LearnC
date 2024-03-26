//
// Created by 张宜鹏 on 2022/11/2.
//
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>


/**
 * C 库宏 offsetof(type, member-designator) 会生成一个类型为 size_t 的整型常量，它是一个结构成员相对于结构开头的字节偏移量。
 * 成员是由 member-designator 给定的，结构的名称是在 type 中给定的。
 *
 * 该宏返回类型为 size_t 的值，表示 type 中成员的偏移量
 * 任意类型的指针都占4个字节
 */
struct address {
    char name[100];
    char street[100];
    int phone;// 20
    const char *format;//24
    int age;// 32
    const char *codec;//40
    int sex;//48
};


extern int errno;

int main() {
    struct address addr = {
            .format = "aaaaaaaaa"
    };

    printf("address 结构中的 name 偏移 = %d 字节。\n",
           offsetof(struct address, name));

    printf("address 结构中的 street 偏移 = %d 字节。\n",
           offsetof(struct address, street));

    printf("address 结构中的 phone 偏移 = %d 字节。\n",
           offsetof(struct address, phone));

    printf("address 结构中的 format 偏移 = %d 字节。\n",
           offsetof(struct address, format));

    printf("address 结构中的 age 偏移 = %d 字节。\n",
           offsetof(struct address, age));

    printf("address 结构中的 codec 偏移 = %d 字节。\n",
           offsetof(struct address, codec));

    printf("address 结构中的 sex 偏移 = %d 字节。\n",
           offsetof(struct address, sex));


    printf("sizeof(char) = %d 字节。\n", sizeof(const char));
    printf("sizeof(char*) = %d 字节。\n", sizeof(const char *));
    printf("sizeof(int*) = %d 字节。\n", sizeof(const int *));
    printf("sizeof(long*) = %d 字节。\n", sizeof(const long *));
    printf("sizeof(addr.format) = %d 字节。\n", sizeof(addr.format));
    printf("sizeof(char[50]) = %d 字节。\n", sizeof(const char[50]));


    assert(1 < 2);

    FILE *fp;

    fp = fopen("file.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    } else {
        fclose(fp);
    }


    return (0);
}