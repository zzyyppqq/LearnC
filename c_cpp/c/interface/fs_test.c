//
// Created by 张宜鹏 on 2022/11/3.
//

#include "fs_interface.h"
#include "ext2_fs.h"

int main() {
    // find ext2 file_system_interface by name "ext2"
    file_system_interface fsi;
    int flags = 0;
    // call open_file
    int fd = fsi.pmethods->open_file(fsi.pfs, "path", flags);
    return fd;
}