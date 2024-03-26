//
// Created by 张宜鹏 on 2023/2/2.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char str[30];
    gets(str);
    printf("%s\n", str);

    //char *pstr = "123";
    char *pstr = (char*)malloc(20*sizeof(char));
    gets(pstr);
    printf("%s\n", pstr);
    return 0;
}