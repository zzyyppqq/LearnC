//
// Created by 张宜鹏 on 2023/2/17.
//

#include "stdio.h"
#include "string.h"

int main() {
    int arr[5];
    arr[1] = 1;
    arr[2] = 2;
    arr[3] = 3;
    // 模拟数据，int数组arr 实际长度 为 3
    printf("---int[]----%d\n", sizeof(arr) / sizeof(arr[0]));

    char str[5];
    str[0] = 'a';
    str[1] = 'b';
    str[2] = 'c';
    // 模拟数据，char数组arr 实际长度 为 3
    printf("---char[]----%d\n", sizeof(str) / sizeof(str[0]));
    printf("---char[]----%d\n", strlen(str));
    return 0;
}