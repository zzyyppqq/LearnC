//
// Created by aecg on 2024/3/25.
//

#include "folder.h"
#include <string.h>
#include <stdio.h>


static void Operation(struct FileSystemNode *this) {
    printf("操作文件夹%s\n", this->nodeName);
    for (int i = 0; i < 100; ++i) {
        if (this->childList[i] != NULL) {
            this->childList[i]->Operation(this->childList[i]);
        }
    }
}

static void Add(struct FileSystemNode *this, struct FileSystemNode *node) {
    for (int i = 0; i < 100; ++i) {
        if (this->childList[i] == NULL) {
            this->childList[i] = node;
            printf("增加子节点%s\n", node->nodeName);
            return;
        }
    }
    printf("error: 增加子节点失败\n");
}

static void Remove(struct FileSystemNode *this, struct FileSystemNode *node) {
    for (int i = 0; i < 100; ++i) {
        if (this->childList[i] != node) {
            this->childList[i] = NULL;
            printf(" 删除子节点%s\n", node->nodeName);
            return;
        }
    }
    printf("error: 删除子节点失败\n");
}


void Folder(struct FileSystemNode *this, char* nodeName) {
    strcpy(this->nodeName, nodeName);
    memset(this->childList, 0, sizeof (this->childList));
    this->Operation = Operation;
    this->Add = Add;
    this->Remove = Remove;
}

void _Folder(struct FileSystemNode *this) {
    memset(this->nodeName, 0 , sizeof (this->nodeName));
    memset(this->childList, 0, sizeof (this->childList));
    this->Operation = NULL;
    this->Add = NULL;
    this->Remove = NULL;
}
