//
// Created by aecg on 2024/3/25.
//

#include <stdio.h>
#include <string.h>
#include "file.h"

static void Operation(struct FileSystemNode *this) {
    printf("操作文件%s\n", this->nodeName);
}

static void Add(struct FileSystemNode *this, struct FileSystemNode *node) {
    printf("error: 文件节点，不支持增加子节点%s\n");
}

static void Remove(struct FileSystemNode *this, struct FileSystemNode *node) {
    printf("error: 文件节点，不支持删除子节点%s\n");
}


void File(struct FileSystemNode *this, char* nodeName) {
    strcpy(this->nodeName, nodeName);
    memset(this->childList, 0, sizeof (this->childList));
    this->Operation = Operation;
    this->Add = Add;
    this->Remove = Remove;
}

void _File(struct FileSystemNode *this) {
    memset(this->nodeName, 0 , sizeof (this->nodeName));
    memset(this->childList, 0, sizeof (this->childList));
    this->Operation = NULL;
    this->Add = NULL;
    this->Remove = NULL;
}
