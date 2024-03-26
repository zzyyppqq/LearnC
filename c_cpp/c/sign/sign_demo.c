//
// Created by 张宜鹏 on 2022/11/2.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int);
void sigterm_handler(int);

int main()
{
    signal(SIGINT, sighandler);

    signal(SIGTERM, sigterm_handler);

    int ret;
    printf("开始生成一个信号\n");
    ret = raise(SIGINT);
    if (ret != 0) {
        printf("错误，不能生成SIGINT信号\n");
        exit(0);
    }

    while(1)
    {
        printf("开始休眠一秒钟...\n");
        sleep(1);
    }

    return(0);
}

void sighandler(int signum)
{
    printf("捕获信号 %d，跳出...\n", signum);
    exit(1);
}

void sigterm_handler(int signum)
{
    printf("捕获信号 %d，跳出...\n", signum);
    exit(1);
}