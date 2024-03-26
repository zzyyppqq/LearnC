//
// Created by 张宜鹏 on 2023/2/14.
//

#include <stdio.h>
#include <stdlib.h>

#define __USE_GNU

#include <dlfcn.h>

#define TEST_MEM_LEAK 1    //值为1表示加入内存泄露的检测，为0表示不加入

#if TEST_MEM_LEAK

typedef void *(*malloc_t)(size_t size);

malloc_t malloc_f = NULL;

typedef void (*free_t)(void *p);

free_t free_f = NULL;

int malloc_flag = 1;    // 用于防止重复递归无法退出,因为printf函数会调用malloc进行内存分配
int free_flag = 1;

void *malloc(size_t size) {
    if (malloc_flag) {
        malloc_flag = 0;  // 用于防止printf造成递归调用malloc而出错
        printf("malloc\n");
        void *p = malloc_f(size);
        malloc_flag = 1;  // 用于保证后续再次调用本文件中malloc时flag标志的初始值一致
        return p;
    } else {
        return malloc_f(size);  // 这里调用dlsym获取的系统库中malloc函数
    }
}

void free(void *p) {
    if (free_flag) {
        free_flag = 0;
        printf("free\n");
        free_f(p);
        free_flag = 1;
    } else {
        free_f(p);
    }
}

#endif


// dlsym函数还可实现对库函数malloc与free的包装来检测我们的代码是否存在内存泄漏（malloc与free若不成对则存在内存泄漏）
int main(int argc, char **argv) {
#if TEST_MEM_LEAK    // 这里if到endif之间的部分可分装成函数调用
    malloc_f = dlsym(RTLD_NEXT, "malloc");
    if (!malloc_f) {
        printf("load malloc failed: %s\n", dlerror());
        return 1;
    }
    free_f = dlsym(RTLD_NEXT, "free");
    if (!free_f) {
        printf("load free failed: %s\n", dlerror());
        return 1;
    }
#endif
    void *p1 = malloc(10);  //这里会先调用本文中的malloc函数
    void *p2 = malloc(20);
    //这里的p2未释放存在内存泄漏，通过利用查看打印的malloc与free次数是否一样来判断
    free(p1);
    return 0;
}