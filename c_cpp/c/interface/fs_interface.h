//
// Created by 张宜鹏 on 2022/11/3.
//

#ifndef CPPSTUDY_FS_INTERFACE_H
#define CPPSTUDY_FS_INTERFACE_H

// 接口函数指针类型
typedef int (*open_file_fn)(void *pfs, const char *path, int flags);

typedef int (*read_file_fn)(void *pfs, int fd, char *buf, int len);


// 接口方法集
typedef struct fs_methods_t {
    open_file_fn open_file;
    read_file_fn read_file;
} fs_methods_t;


// 接口的实现体
typedef struct file_system_interface {
    void *pfs;              // 文件系统的具体实现struct
    fs_methods_t *pmethods; // 这个文件系统的具体接口方式实现
} file_system_interface;


// 各个文件系统，通过 register_file_system 将自己注册进内核
// const char* pname;           // 文件系统的名称，如ext2, xfs...
int register_file_system(const char *pname, file_system_interface fsi);


#endif //CPPSTUDY_FS_INTERFACE_H
