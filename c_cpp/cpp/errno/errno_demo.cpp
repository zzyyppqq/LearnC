//
// Created by 张宜鹏 on 2023/2/6.
//
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sched.h>

extern int errno;

int main() {

    FILE *fp;

    fp = fopen("file.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    } else {
        fclose(fp);
    }

    int i;
    for (i = 0; i < 140; ++i) {
        errno = i;
        printf("errno %d :\t\t%s\n", i, strerror(errno));
    }



    return (0);
}