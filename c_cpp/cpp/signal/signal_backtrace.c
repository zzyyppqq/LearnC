//
// Created by zhangyipeng on 2023/8/16.
//

#include <stdio.h>
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>
#include <malloc/_malloc.h>


void sigHandler(int signo) {
    printf("=====recv SIGINT %d=====\n", signo);

    //打印错误堆栈信息
    printf("----------------------------Dump Program Error Strings-------------------------\n");
    int j = 0, nptrs = 0;
    void *buffer[100] = {NULL};
    char **strings = NULL;
    nptrs = backtrace(buffer, 100);
    printf("backtrace() returned %d addresses\n", nptrs);
    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        printf("backtrace_symbols null\n");
        printf("-------------------------------------------------------------------------------\n");
        return;
    }
    for (j = 0; j < nptrs; j++) {
        printf("  [%02d] %s\n", j, strings[j]);
    }
    free(strings);
    printf("-------------------------------------------------------------------------------\n");

    //恢复默认信号操作
    signal(signo, SIG_DFL);
    raise(signo);
}

void test(int *ptr) {
    *ptr = 6;
}

int main() {
    printf("start\n");
    signal(SIGSEGV, sigHandler);
    signal(SIGABRT, sigHandler);

    int *ptr = NULL;
    //test(ptr);
    test(&ptr);

    int i = 0;
    while (++i) {
        printf("Going to sleep....\n");
        if (i == 3) {
            raise(SIGSEGV);
        }
        sleep(1);
    }
    return 1;
}