//
// Created by 张宜鹏 on 2023/2/21.
//

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void handler() {
    printf("hello\n");
}

int main() {
    int i;
    signal(SIGALRM, handler);
    alarm(5);
    for (i = 1; i < 7; i++) {
        printf("sleep %d ...\n", i);
        sleep(1);
    }
    return 0;
}
