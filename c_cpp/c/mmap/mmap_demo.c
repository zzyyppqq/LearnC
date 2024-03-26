//
// Created by 张宜鹏 on 2023/2/16.
//
/**
 * 　　从程序的运行结果中可以得出的结论
　　1、 最终被映射文件的内容的长度不会超过文件本身的初始大小，即映射不能改变文件的大小；
　　2、可以用于进程通信的有效地址空间大小大体上受限于被映射文件的大小，但不完全受限于文件大小。打开文件被截短为5个people结构大小，而在 map_normalfile1中初始化了10个people数据结构，在恰当时候（map_normalfile1输出initialize over 之后，输出umap ok之前）调用map_normalfile2会发现map_normalfile2将输出全部10个people结构的值，后面将给出详细讨论。
　　注：在linux中，内存的保护是以页为基本单位的，即使被映射文件只有一个字节大小，内核也会为映射分配一个页面大小的内存。当被映射文件小于一个页面大小时，进程可以对从mmap()返回地址开始的一个页面大小进行访问，而不会出错；但是，如果对一个页面以外的地址空间进行访问，则导致错误发生，后面将进一步描述。因此，可用于进程间通信的有效地址空间大小不会超过文件大小及一个页面大小的和。
　　3、文件一旦被映射后，调用mmap()的进程对返回地址的访问是对某一内存区域的访问，暂时脱离了磁盘上文件的影响。所有对mmap()返回地址空间的操作只在内存中有意义，只有在调用了munmap()后或者msync()时，才把内存中的相应内容写回磁盘文件，所写内容仍然不能超过文件的大小。
 */

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
    char name[4];
    int age;
} people;

int main(int argc, char **argv) {
    // map a normal file as shared mem:

    int fd, i;
    people *p_map;
    char temp;

    fd = open("data.txt", O_CREAT | O_RDWR | O_TRUNC, 00777);
    lseek(fd, sizeof(people) * 5 - 1, SEEK_SET);
    write(fd, "", 1);
    p_map = (people *) mmap(NULL, sizeof(people) * 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    temp = 'a';
    for (i = 0; i < 10; i++) {
        temp += 1;
        memcpy((*(p_map + i)).name, &temp, 2);
        (*(p_map + i)).age = 20 + i;
    }
    printf("initializeover\n");
//    msync(p_map, sizeof(people) * 10, MS_SYNC);
//    printf("msync\n");
    sleep(10);
    munmap(p_map, sizeof(people) * 10);
    printf("umapok\n");
}

