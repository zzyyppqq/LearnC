//
// Created by 张宜鹏 on 2023/3/2.
//

#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

jmp_buf env;

void handler(int signal) {
    printf("caught exception signal: %d\n", signal);
    printf("longjmp() \n");
    longjmp(env, 2);
}
// 如果是从setjmp直接调用返回，setjmp返回值为0。如果是从longjmp恢复的程序调用环境返回，setjmp返回非零值。
int main(int argc, char *argv[]) {
    {
        struct sigaction sa = {};
        sa.sa_handler = handler;
        //sigemptyset(&sa.sa_mask);
        //sa.sa_flags = 0;
        if (sigaction(SIGFPE, &sa, NULL) == -1) {
            perror("sigaction");
        }
    }

    printf("setjmp() \n");
    if (0 == setjmp(env)) {
        printf("3/0\n");
        int a = 3 / (argc - 1);
        printf("a is %d\n", a);
    } else {
        //exception
        printf("in exception\n");
    }

    return 1;
}