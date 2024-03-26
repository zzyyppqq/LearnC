//
// Created by aecg on 2024/3/25.
//

#ifndef LEARNC_FILE_SYSTEM_NODE_H
#define LEARNC_FILE_SYSTEM_NODE_H

struct FileSystemNode {
    char nodeName[100];
    struct FileSystemNode *childList[100];
    void (*Operation)(struct FileSystemNode *this);
    void (*Add)(struct FileSystemNode *this, struct FileSystemNode *node);
    void (*Remove)(struct FileSystemNode *this, struct FileSystemNode *node);
};

#endif //LEARNC_FILE_SYSTEM_NODE_H
