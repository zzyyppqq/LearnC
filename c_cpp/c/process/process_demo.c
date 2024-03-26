//
// Created by zhangyipeng on 2023/11/7.
//
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NAMELEN 16



void print_thread_name() {
    char thread_name[NAMELEN];
    int rc = pthread_getname_np(pthread_self(), thread_name, NAMELEN);
    pthread_t tid = pthread_self();
    printf("当前线程的 ID 是：%lu\n", tid);
    if (rc == 0) {
        printf("thread name: %s\n", thread_name);
    }
}

int main() {
    printf("start...\n");
    pthread_setname_np("main_thread");
    pid_t child_pid;
    child_pid = fork();
    if (child_pid == 0) {
        // 这里是子进程的代码
        printf("sub process\n");
        pthread_setname_np("sub_thread");
        print_thread_name();
    } else if (child_pid > 0) {
        // 这里是父进程的代码
        printf("parent process\n");
        print_thread_name();
    } else {
        // 错误处理
    }
    sleep(2);
    print_thread_name();
    return 0;
}