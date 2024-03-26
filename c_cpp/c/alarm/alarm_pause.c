//
// Created by 张宜鹏 on 2023/2/21.
//

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

int NAMELEN = 160;

void sig_handler(int num)
{
    char thread_name[NAMELEN];
    pthread_getname_np(pthread_self(), thread_name, NAMELEN);
    printf("sig_handler pid: %d, thread name: %s\n", getpid(), thread_name);
    printf("receive the signal %d.\n", num);
    alarm(2);
}
int main()
{
    pthread_setname_np("main thread");
    char thread_name[NAMELEN];
    pthread_getname_np(pthread_self(), thread_name, NAMELEN);
    printf("main pid: %d, thread name: %s\n", getpid(), thread_name);

    signal(SIGALRM, sig_handler);
    alarm(2);
    while(1)//做一个死循环，防止主线程提早退出，相等于线程中的join
    {
        pause();//pause()函数使该进程暂停让出CPU
    }
    //pause();//如果没有做一个死循环则只会让出一次cpu然后就还给主线程，主线程一旦运行结束就会退出程序
    exit(0);
}
