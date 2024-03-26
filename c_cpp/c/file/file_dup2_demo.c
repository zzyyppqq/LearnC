//
// Created by 张宜鹏 on 2023/2/18.
//
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/syscall.h>

void main() {
//    syscall(SYS_close, 0);
//    syscall(SYS_close, 1);
//    syscall(SYS_close, 2);

    int oldfd;
    int fd;
    int t;
    char *buf = "This is a test!!!!\n";
    if ((oldfd = open("mine.txt", O_RDWR | O_CREAT, 0644)) == -1) {
        printf("open error\n");
        exit(-1);
    }
    printf("start\n");
    fd = dup2(oldfd, STDOUT_FILENO);
//    fd = dup2(oldfd, fileno(stdout));
    if (fd == -1) {
        printf("dup2 error\n");
        exit(-1);
    }
    printf("dup2的返回值：%d\n", fd);
    t = strlen(buf);
    printf("buf size：%d\n", t);
    if (write(fileno(stdout), buf, t) != t)//本应该写入到stdout的信息，但是标准输出已经重定向到目标文件中，故向标准输出写的数据将会写到目标文件中。
    {
        printf("write error!\n");
        exit(-1);
    }
    close(fd);
    printf("end\n");
    exit(0);
}