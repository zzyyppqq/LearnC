//
// Created by 张宜鹏 on 2022/11/2.
//

#include <stdio.h>
#include <dlfcn.h>

void swap(int *p1, int *p2);

void test1();

void test2();

void testArray();

/**
 * 点（.）是用于结构体变量访问成员，箭头（->）是用于结构体指针访问成员。
 * @return
 */
int main(void) {
    test1();
    test2();

    testArray();

    dlopen("", "rb");

    struct Smy {
        int a;
    };
    struct Smy test;
    struct Smy *pt;
    test.a = 1;
    pt = &test;

    printf("%d\n", test.a);
    printf("%d\n", pt->a);

    int i = 10;
    int *p = &i;
//    int &r = i; // c不支持
//    int &b=10;//error

    printf("指针（地址）的值为p(16进制地址)：%p\n", p);
    printf("指针（地址）的值为p(long)：%lld\n", p);
    printf("指针（地址）的值为&i(16进制地址)：%p\n", &i);
    printf("指针（地址）的值为&i(long)：%lld\n", &i);
    printf("指针（地址）的值为*p：%d\n", *p);
    printf("变量的值为：%d\n", i);

    printf("==============================\n", i);

    int a = 1, b = 3;
    int *p1 = &a, *p2 = &b;

    // 交换前
    printf("交换前：a=%d,b=%d \n", *p1, *p2);
    printf("交换前(地址)：p1=%p \n", p1);
    printf("交换前(地址)：p2=%p \n", p2);
    // 交换中
    swap(p1, p2);
    // 交换后
    printf("交换后：a=%d,b=%d \n", *p1, *p2);
    printf("交换后(地址)：p1=%p \n", p1);
    printf("交换后(地址)：p2=%p \n", p2);

}

void testArray() {
    FILE *pFile;
    char szFilename[32];
    int y;

    // Open file
    sprintf(szFilename, "test%d.txt", 1);
    pFile = fopen(szFilename, "wb");
    if (pFile == NULL)
        return;

    // Write header
    fprintf(pFile, "Test_%dx%d\n", 10, 20);
    int b[6]={1,3,5,7,9,11};
    printf("sizeof(int): %d\n", sizeof(int));
    printf("b = %p\n", b);
    printf("b[0] = %p\n", b[0]);
    printf("b[1] = %p\n", b[1]);
    fwrite(b, sizeof(int), 6, pFile);

}

void swap(int *p1, int *p2) {

    int *temp = p1;
    p1 = p2;
    p2 = temp;
    printf("交换中：a=%d,b=%d \n", *p1, *p2);
    printf("交换中(地址)：p1=%p \n", p1);
    printf("交换中(地址)：p2=%p \n", p2);
}

void test1() {
    typedef struct {
        int data[20];
        int length;
    } Sqlist;

    Sqlist L;
    L.length; //直接调用L中length的值
    L.data[3];
}

void test2() {
    // 指向结构体成员运算符 : (->) 从外部看是包含了一个解指针（*）所以要对指针进行操作
    typedef struct {
        int data[20];
        int length;
    } Sqlist; //与上面完全一样

    Sqlist *L;
    L->length; //同样是得到L中length的值
}
