//
// Created by 张宜鹏 on 2022/11/3.
//
#include "ext2_fs.h"

// 接口方法实现集合
fs_methods_t ext2_methods = {
        .open_file = (open_file_fn) ext2_open_file,
        .read_file = (read_file_fn) ext2_read_file,
};


// 服务实例
ext2_fs_t g_ext2_fs;


int ext2_init(void) {
    // init g_ext2_fs struct ....
    // ....

    file_system_interface fsi = {.pfs = &g_ext2_fs, .pmethods = &ext2_methods};
    int ret = register_file_system("ext2", fsi);
    return ret;
}


int ext2_open_file(ext2_fs_t *pfs, const char *path, int flags) {
    // ....
}


int ext2_read_file(ext2_fs_t *pfs, int fd, char *buf, int len) {
    // ....
}