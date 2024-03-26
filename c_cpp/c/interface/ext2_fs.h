//
// Created by 张宜鹏 on 2022/11/3.
//

#ifndef CPPSTUDY_EXT2_FS_H
#define CPPSTUDY_EXT2_FS_H

#include "fs_interface.h"


typedef struct ext2_fs_t {
    // ......
} ext2_fs_t;


int ext2_open_file(ext2_fs_t* pfs, const char* path, int flags);
int ext2_read_file(ext2_fs_t* pfs, int fd, char* buf, int len);


int ext2_init(void);

#endif //CPPSTUDY_EXT2_FS_H
