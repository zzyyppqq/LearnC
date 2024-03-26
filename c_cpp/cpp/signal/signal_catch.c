//
// Created by 张宜鹏 on 2023/2/2.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
//#include <sys/eventfd.h>
// linux - eventfd 的 OS X 替代品
// pipe 和kqueue 的EVFILT_USER
#include <sys/event.h>

#define SIGNAL_CRASH_STACK_SIZE (1024 * 128)

static int notifier = -1;

void handle_exception();

static void sig_func(int sig_num, struct __siginfo *info, void *ptr) {
    uint64_t data;
    data = sig_num;
    printf("catch signal %llu %d\n", data, notifier);
    printf("siginfo pid: %d\n", info->si_pid);

    if (notifier >= 0) {
        write(notifier, &data, sizeof data);
    }
}

void init_with_signal(int *signals, int size, void (*handler)(int, struct __siginfo *, void *)) {

    int needMask = 0;

    for (int i = 0; i < size; i++) {
        if (signals[i] == SIGQUIT) {
            needMask = 1;
        }
    }

    do {
        sigset_t mask;
        sigset_t old;
        // 这里需要stack_t，临时的栈，因为SIGSEGV时，当前栈空间已经是处于进程所能控制的栈中，此时就不能在这个栈里面操作，否则就会异常循环
        stack_t ss;
        if (NULL == (ss.ss_sp = calloc(1, SIGNAL_CRASH_STACK_SIZE))) {
            handle_exception();
            break;
        }
        ss.ss_size = SIGNAL_CRASH_STACK_SIZE;
        ss.ss_flags = 0;
        if (0 != sigaltstack(&ss, NULL)) {
            handle_exception();
            break;
        }

        if (needMask) {
            sigemptyset(&mask);
            sigaddset(&mask, SIGQUIT);
            if (0 != pthread_sigmask(SIG_UNBLOCK, &mask, &old)) {
                break;
            }
        }


        struct sigaction sigc;

        sigc.sa_sigaction = handler;
        sigemptyset(&sigc.sa_mask);
        sigc.sa_flags = SA_SIGINFO | SA_ONSTACK;

        // 注册所有信号
        for (int i = 0; i < size; i++) {
            // 这里不需要旧的处理函数
            // 指定SIGKILL和SIGSTOP以外的所有信号
            int flag = sigaction(signals[i], &sigc, NULL);
            if (flag == -1) {
                printf("register fail ===== signals[%d] ", i);
                handle_exception();
                // 失败后需要恢复原样
                if (needMask) {
                    pthread_sigmask(SIG_UNBLOCK, &old, NULL);
                }
                break;
            }
        }
    } while (0);
}

void handle_exception() {
    printf("---- handle_exception ----\n");
}

static void* invoke_crash(void *arg){
    printf("---- invoke_crash ----\n");
}

int main() {
    int size = 5;
    int signals[5] = {SIGINT, SIGQUIT, SIGILL, SIGTRAP, SIGBUS};
    printf("init_with_signal\n");
    init_with_signal(signals, size, sig_func);

    //notifier = eventfd(0,EFD_CLOEXEC);

    // 启动异步线程
    pthread_t thd;
    printf("pthread_create\n");
    if(0 != pthread_create(&thd, NULL,invoke_crash, NULL)){
        printf("close\n");
        handle_exception();
        close(notifier);
        notifier = -1;
    }
    printf("ok\n");
    int i = 0;
    while (++i) {
        printf("Going to sleep....\n");
        if (i == 3) {
            printf("SIGINT\n");
            raise(SIGINT);
        }
        sleep(1);
    }

    return 1;
}