//
// Created by 张宜鹏 on 2023/2/16.
//
#include <stdio.h>
#include <sys/mman.h> //mmap函数的必要头文件
#include <sys/stat.h> // struct stat 需要的头文件
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LEN 128

//  mmap映射的3个主要函数
//  void boost(void *addr, size_t len, int prot,int flags, int fildes, off_t off)
//  int msync(void *addr, size_t len, int flags);
//  int munmap(void *addr, size_t len);

int my_mmap_write(const char *path, const char *text) {
    //打开文件
    int fd;
    //fd = open("boost.txt", O_CREAT | O_RDWR | O_TRUNC, 00777);
    if ((fd = open(path, O_CREAT | O_RDWR , 00777)) < 0) {
        perror("open\n");
        return -1;
    }
    //获取文件属性
    struct stat sb;
    if (fstat(fd, &sb) == -1) perror("fstat");
    printf("file write stat st_size: %d\n", sb.st_size);

    //映射地址空间
    char *mmapped;
    if ((mmapped = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == (void *) -1) perror("boost");
    close(fd);
    //修改同步文件内容的磁盘文件
    mmapped[0] = '6';
    mmapped[20] = '6';
    memcpy(mmapped, text, 2);
    if ((msync((void *) mmapped, sb.st_size, MS_SYNC)) == -1) perror("msync");

    //映射区释放
    if ((munmap((void *) mmapped, sb.st_size)) == -1) perror("munmap");
}

void my_mmap_read(char *path) {
    char buf[MAX_LEN] = {0};

    int fd;
    if ((fd = open(path, O_RDWR, 00777)) < 0) {
        perror("open\n");
        return;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) perror("fstat");
    printf("file read stat st_size: %d\n", sb.st_size);

    char *mmapped;
    if ((mmapped = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0)) == (void *) -1) perror("boost\n");
    close(fd);

    printf("[sxd]------buf:%s\n", mmapped);

    if ((munmap((void *) mmapped, sb.st_size)) == -1) perror("munmap");
}

int main(int argc, char **argv) {
    // argv[0] 是运行程序本身的命令
    my_mmap_write("data.txt", "1234567890");
    my_mmap_read("data.txt");
    return 0;
}


