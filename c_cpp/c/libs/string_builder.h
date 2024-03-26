//
// Created by zhangyipeng on 2023/11/7.
//

#ifndef CPPSTUDY_STRING_BUILDER_H
#define CPPSTUDY_STRING_BUILDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *buffer;
    size_t length;
    size_t capacity;
} StringBuilder;

void StringBuilder_init(StringBuilder *sb) {
    sb->buffer = (char *)malloc(16 * sizeof(char));  // 初始分配 16 个字节的内存
    sb->buffer[0] = '\0';
    sb->length = 0;
    sb->capacity = 16;
}

void StringBuilder_append(StringBuilder *sb, const char *str) {
    size_t new_length = sb->length + strlen(str);
    if (new_length + 1 > sb->capacity) {
        while (new_length + 1 > sb->capacity) {
            sb->capacity *= 2;  // 如果需要更多的空间，扩大容量为当前的两倍
        }
        sb->buffer = (char *)realloc(sb->buffer, sb->capacity);
    }
    strcat(sb->buffer, str);
    sb->length = new_length;
}

void StringBuilder_free(StringBuilder *sb) {
    free(sb->buffer);
    sb->buffer = NULL;
    sb->length = 0;
    sb->capacity = 0;
}


#endif //CPPSTUDY_STRING_BUILDER_H
