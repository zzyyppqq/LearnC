//
// Created by 张宜鹏 on 2022/4/28.
//

#include "mylib.h"
#include "stdio.h"
#include "string.h"

int main(int argc, char **argv) {

    MyNumber myNumber = MyNumber();
    myNumber.setNumber(1,2);
    myNumber.printMsg();

    printf("argc = %d\n", argc);
    for (int i = 0; i< argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    char cmd[100] = "ffplay -ii test1.mp4";
    char *p = strtok(cmd, " ");
    argc = 0;
    if(p){
        printf("==>%s\n", p);
        argv[argc] = p;
        argc++;
    }
    while(p=strtok(NULL, " ")){
        //使用第一个参数为NULL来提取子串
        printf("-->%s\n", p);
        argv[argc] = p;
        argc++;
    }

    printf("argc = %d\n", argc);
    for (int i = 0; i< argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    printf("File    Fame: %s\n", __FILE__);      //文件名
    printf("Present Line: %d\n", __LINE__);      //所在行
    printf("Present Function: %s\n", __func__);  //函数名

    printf("Present Function: %s():%d\n", __func__, __LINE__);  //函数名
}