//
// Created by 张宜鹏 on 2023/2/17.
//

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/file.h>


const char* file_dir = "/Users/zhangyipeng/CLionProjects/CppStudy/c_cpp";
const char* file_name = "data.txt";

// chmod(2), close(2), dup(2), getdtablesize(2), lseek(2), read(2),
//     umask(2), write(2)
int main() {
    char file_path[256] = {0};
    strcat(file_path, file_dir);
    strcat(file_path + strlen(file_dir), "/");
    strcat(file_path + strlen(file_dir) + 1, file_name);
    printf("file_path: %s, len: %d\n", file_path, strlen(file_path));


    int len = 11;
    char *str_ptr = "abcdefghijk";
    int fd = open("data.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        printf("file open failed\n");
    }
    printf("pagesize: %d\n", getpagesize());
    printf("tablesize: %d\n", getdtablesize());
    // ftruncate() 文件大小超过长度，任何额外的数据都将被丢弃。如果文件大小小于长度，文件被扩展并用零填充到指示长度
    int ft = ftruncate(fd, len);
    if(ft == -1) {
        printf("ftruncate failed\n");
    }
    int8_t *mmap_ptr = (int8_t *) mmap(0, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mmap_ptr == MAP_FAILED) {
        printf("mmap failed\n");
    }
    memcpy(mmap_ptr, str_ptr, len);
    // msync() 系统调用将修改后的整个页面写回文件系统并更新文件修改时间
    msync(mmap_ptr, len, MS_SYNC);
    munmap(mmap_ptr, len);

    dup(getpid());
    return 0;
}