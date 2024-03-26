//
// Created by 张宜鹏 on 2023/2/18.
//
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
    int fd = open("text.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        printf("Open Error!\n");
        return 0;
    }
    //dup(oldfd)等效 fcntl(oldfd, F_DUPFD, 0)
    int fd2 = dup(fd);
    //int fd3 = fcntl(fd, F_DUPFD, 0);
    if (fd2 < 0) {
        printf("Error!\n");
        return 0;
    }
    char buf[1000];
    int n;
    while ((n = read(STDIN_FILENO, buf, 1000)) > 0)  //接受键盘输入，并将其存入buf所指向的缓存中
    {
        if (write(fd2, buf, n) < n)    //将buf所指向的缓存区的n个字节的数据写入到由文件描述符fd2所指示的文件中
        {
            printf("Write Error!!\n");
            return 0;
        }
    }
    return 0;
}