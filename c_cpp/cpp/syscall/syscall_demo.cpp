//
// Created by 张宜鹏 on 2023/2/3.
//

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/uio.h>

pid_t gettid() {
    pid_t tid;
    //tid = syscall(SYS_gettid); // linux
    tid = syscall(SYS_thread_selfid); // mac
    return tid;
}

void *hello(void *s){
    printf("%s()\t, line = %d\t, getpid() = %#x\n",__FUNCTION__,__LINE__,getpid());
    printf("%s()\t, line = %d\t, pthread_self() = %#x\t, SYS_gettid = %#x\n",__FUNCTION__,__LINE__,pthread_self(),syscall(SYS_gettid));
}

int main(int argc, char *argv[]) {

    pid_t tid_ = gettid();
    printf("tid: %d\n", tid_);
    printf("pid: %d\n", getpid());
    printf("ppid: %d\n", getppid());


    std::cout << "getpid()=" << getpid() << std::endl;
    std::cout << "pthread_self()=" << pthread_self() << std::endl;
    uint64_t tid;
    pthread_threadid_np(NULL, &tid);
    std::cout << "pthread_threadid_np()=" << tid << std::endl;
    std::cout << "syscall(SYS_thread_selfid)=" << syscall(SYS_thread_selfid) << std::endl;
    std::cout << "syscall(SYS_gettid)=" << syscall(SYS_gettid) << std::endl;



    printf("%s()\t, line = %d\t, getpid() = %#x\n",__FUNCTION__,__LINE__,getpid());
    printf("%s()\t, line = %d\t, pthread_self() = %#x\t, SYS_gettid = %#x\n",__FUNCTION__,__LINE__,pthread_self(),syscall(SYS_gettid));

    pthread_t thread_id;
    pthread_create(&thread_id,NULL,hello,NULL);
    pthread_join(thread_id,NULL);


//    int ret = execl("/usr/local/bin/tree", "tree", "-l", NULL);
//    printf("execl ret: %d\n", ret);
//    if (ret == 0) {
//        printf("execl success!\n");
//    }



    int xc_crash_log_fd = getpid();
    int i;
    for(i = 0; i < 124; i++) {
        if (i != xc_crash_log_fd) {
            printf("SYS_close i: %d\n", i);
            int ret = syscall(SYS_close, i);
            printf("SYS_close ret: %d, SYS_close: %d\n", ret, SYS_close);
        }
    }

    printf("syscall\n");
    return 1;
}