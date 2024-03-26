//
// Created by 张宜鹏 on 2023/2/16.
//

#include<sys/mman.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/stat.h>

typedef struct {
    char name[4];
    int age;
} people;


void main(int argc, char **argv) {
    //map a normal file as shared mem:

    int fd, i;
    people *p_map;
    fd = open("data.txt", O_CREAT | O_RDWR, 00777);
    struct stat sb;
    if(fstat(fd, &sb) == -1)  perror("fstat");

    p_map = (people *) mmap(NULL, sizeof(people) * 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    for (i = 0; i < 10; i++) {
        printf("name: %s, age: %d\n", (*(p_map + i)).name, (*(p_map + i)).age);
    }
    munmap(p_map, sizeof(people) * 10);
}