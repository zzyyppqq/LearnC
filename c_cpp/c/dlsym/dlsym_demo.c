//
// Created by 张宜鹏 on 2023/2/14.
//


#include <stdio.h>
#include <stdlib.h>

#define __USE_GNU     //使用RTLD_DEFAULT和RTLD_NEXT宏需定义

#include <dlfcn.h>

typedef size_t (*strlen_t)(const char *);

strlen_t strlen_f = NULL, strlen_f1 = NULL;

size_t strlen(const char *str) {
    printf("%s strlen\n", __FILE__);
    return strlen_f1(str);
}

// RTLD_DEFAULT表示按默认的顺序搜索共享库中符号symbol第一次出现的地址
// RTLD_NEXT表示在当前库以后按默认的顺序搜索共享库中符号symbol第一次出现的地址
int main(int argc, char **argv) {
    strlen_f = dlsym(RTLD_DEFAULT, "strlen");
    //获取到的是当前文件中函数符号strlen的地址
    if (!strlen_f) {
        printf("default load error %s\n", dlerror());
        return 1;
    }
    strlen_f1 = dlsym(RTLD_NEXT, "strlen");
    //获取到的是当前库后的系统库中函数符号strlen的地址
    if (!strlen_f1) {
        printf("next load error %s\n", dlerror());
        return 1;
    }
    printf("strlen is %p\n", strlen);
    printf("strlen_f is %p\n", strlen_f);
    printf("strlen_f1 is %p\n", strlen_f1);
    printf("strlen_f is %ld\n", strlen_f("xuedaon")); //调用当前文件中的函数strlen
    printf("=>>>>>>>>>> <<<<<<<<<<<=\n");
    printf("strlen_f1 is %ld\n", strlen_f1("xuedaon"));  //相当于调用系统库函数strlen


    printf("=>>>>>>>>>> <<<<<<<<<<<=\n");
    // libhello.so是我们自己封装的一个测试的共享库文件
    // RTLD_LAZY 表示在对符号引用时才解析符号，但只对函数符号引用有效，而对于变量符号的引用总是在加载该动态库的时候立即绑定解析
    void *handle = dlopen("./lib/libhello.dylib", RTLD_LAZY);
    if (!handle) {
        printf("open failed: %s\n", dlerror());
        return 1;
    }
    void *p = dlsym(handle, "hello");
    if (!p) {
        printf("load failed: %s\n", dlerror());
        return 1;
    }
    void (*fp)() = (void (*)()) p;
    fp();

    void *p1 = dlsym(handle, "global");
    if (!p1) {
        printf("load failed: %s\n", dlerror());
        return 1;
    }
    int global = *(int *) p1;
    printf("global is %d\n", global);

    dlclose(handle);

    return 0;
}