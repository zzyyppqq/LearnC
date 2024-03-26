//
// Created by 张宜鹏 on 2022/11/2.
//


#include <stdio.h>
#include <stdlib.h>

static void (*program_exit)(int ret);

void register_exit(void (*cb)(int ret)) {
    program_exit = cb;
    printf("register_exit\n");
}

void exit_program(int ret) {
    printf("exit_program\n");
    if (program_exit)
        program_exit(ret);

    exit(ret);
}

static void ffmpeg_cleanup(int ret) {
    printf("ffmpeg_cleanup\n");
}

int main() {
    register_exit(ffmpeg_cleanup);

    exit_program(1);
    return 0;
}