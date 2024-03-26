//
// Created by 张宜鹏 on 2022/8/11.
//

/**
 * BSD Socket编程详解
 * https://blog.csdn.net/auspark/article/details/105049667
 * 使用select select这个系统调用，是一种多路复用IO方案，可以同时对多个文件描述符进行监控，从而知道哪些文件描述符可读，可写或者出错，不过select方法是阻塞的，可以设定超时时间。 select使用的步骤如下:
 * 1.创建一个fd_set变量（fd_set实为包含了一个整数数组的结构体），用来存放所有的待检查的文件描述符
 * 2.清空fd_set变量，并将需要检查的所有文件描述符加入fd_set
 * 3.调用select。若返回-1，则说明出错;返回0,则说明超时，返回正数，则为发生状态变化的文件描述符的个数
 * 4.若select返回大于0,则依次查看哪些文件描述符变的可读，并对它们进行处理
 * 5.返回步骤2，开始新一轮的检测 若上面的聊天程序使用select进行改写，则是下面这样的
 */


#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main (int argc, const char * argv[])
{
    struct sockaddr_in server_addr;
    server_addr.sin_len = sizeof(struct sockaddr_in);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(11332);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(server_addr.sin_zero),8);

    int server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock_fd == -1) {
        perror("socket error");
        return 1;
    }
    char recv_msg[BUFFER_SIZE];
    char input_msg[BUFFER_SIZE];

    if (connect(server_sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in))==0) {
        fd_set client_fd_set;
        struct timeval tv;
        tv.tv_sec = 20;
        tv.tv_usec = 0;


        while (1) {
            FD_ZERO(&client_fd_set);
            FD_SET(STDIN_FILENO, &client_fd_set);
            FD_SET(server_sock_fd, &client_fd_set);

            int ret = select(server_sock_fd + 1, &client_fd_set, NULL, NULL, &tv);
            if (ret < 0 ) {
                printf("select 出错!\n");
                continue;
            }else if(ret ==0){
                printf("select 超时!\n");
                continue;
            }else{
                if (FD_ISSET(STDIN_FILENO, &client_fd_set)) {
                    bzero(input_msg, BUFFER_SIZE);
                    fgets(input_msg, BUFFER_SIZE, stdin);
                    if (send(server_sock_fd, input_msg, BUFFER_SIZE, 0) == -1) {
                        perror("发送消息出错!\n");
                    }
                }

                if (FD_ISSET(server_sock_fd, &client_fd_set)) {
                    bzero(recv_msg, BUFFER_SIZE);
                    long byte_num = recv(server_sock_fd,recv_msg,BUFFER_SIZE,0);
                    if (byte_num > 0) {
                        if (byte_num > BUFFER_SIZE) {
                            byte_num = BUFFER_SIZE;
                        }
                        recv_msg[byte_num] = '\0';
                        printf("服务器:%s\n",recv_msg);
                    }else if(byte_num < 0){
                        printf("接受消息出错!\n");
                    }else{
                        printf("服务器端退出!\n");
                        exit(0);
                    }

                }
            }
        }

    }

    return 0;
}


//end

