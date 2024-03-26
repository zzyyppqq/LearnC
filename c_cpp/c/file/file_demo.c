//
// Created by 张宜鹏 on 2023/2/20.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>


int main() {
    printf("fileno(stdin) : %d, STDIN_FILENO: %d\n", fileno(stdin), STDIN_FILENO);
    printf("fileno(stdout): %d, STDOUT_FILENO: %d\n", fileno(stdout), STDOUT_FILENO);
    printf("fileno(stderr): %d, STDERR_FILENO: %d\n", fileno(stderr), STDERR_FILENO);

    FILE   *fp;
    int   fd;
    fp = fopen("data.txt", "r");
    fd = fileno(fp);
    printf("fd = %d\n", fd);
    fclose(fp);
    return 1;
}