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
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#define BACKLOG 5 //完成三次握手但没有accept的队列的长度
#define CONCURRENT_MAX 8 //应用层同时可以处理的连接
#define SERVER_PORT 11332
#define BUFFER_SIZE 1024
#define QUIT_CMD ".quit"
int client_fds[CONCURRENT_MAX];
int main (int argc, const char * argv[])
{
    char input_msg[BUFFER_SIZE];
    char recv_msg[BUFFER_SIZE];
    //本地地址
    struct sockaddr_in server_addr;
    server_addr.sin_len = sizeof(struct sockaddr_in);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(server_addr.sin_zero),8);
    //创建socket
    int server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock_fd == -1) {
        perror("socket error");
        return 1;
    }
    //绑定socket
    int bind_result = bind(server_sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_result == -1) {
        perror("bind error");
        return 1;
    }
    //listen
    if (listen(server_sock_fd, BACKLOG) == -1) {
        perror("listen error");
        return 1;
    }
    //fd_set
    fd_set server_fd_set;
    int max_fd = -1;
    struct timeval tv;
    tv.tv_sec = 20;
    tv.tv_usec = 0;
    while (1) {
        FD_ZERO(&server_fd_set);
        //标准输入
        FD_SET(STDIN_FILENO, &server_fd_set);
        if (max_fd < STDIN_FILENO) {
            max_fd = STDIN_FILENO;
        }
        //服务器端socket
        FD_SET(server_sock_fd, &server_fd_set);
        if (max_fd < server_sock_fd) {
            max_fd = server_sock_fd;
        }
        //客户端连接
        for (int i = 0; i < CONCURRENT_MAX; i++) {
            if (client_fds[i]!=0) {
                FD_SET(client_fds[i], &server_fd_set);

                if (max_fd < client_fds[i]) {
                    max_fd = client_fds[i];
                }
            }
        }
        int ret = select(max_fd+1, &server_fd_set, NULL, NULL, &tv);
        if (ret < 0) {
            perror("select 出错\n");
            continue;
        }else if(ret == 0){
            printf("select 超时\n");
            continue;
        }else{
            //ret为未状态发生变化的文件描述符的个数
            if (FD_ISSET(STDIN_FILENO, &server_fd_set)) {
                //标准输入
                bzero(input_msg, BUFFER_SIZE);
                fgets(input_msg, BUFFER_SIZE, stdin);
                //输入 ".quit" 则退出服务器
                if (strcmp(input_msg, QUIT_CMD) == 0) {
                    exit(0);
                }
                for (int i=0; i<CONCURRENT_MAX; i++) {
                    if (client_fds[i]!=0) {
                        send(client_fds[i], input_msg, BUFFER_SIZE, 0);
                    }
                }
            }
            if (FD_ISSET(server_sock_fd, &server_fd_set)) {
                //有新的连接请求
                struct sockaddr_in client_address;
                socklen_t address_len;
                int client_socket_fd = accept(server_sock_fd, (struct sockaddr *)&client_address, &address_len);
                if (client_socket_fd > 0) {
                    int index = -1;
                    for (int i = 0; i < CONCURRENT_MAX; i++) {
                        if (client_fds[i] == 0) {
                            index = i;
                            client_fds[i] = client_socket_fd;
                            break;
                        }
                    }
                    if (index >= 0) {
                        printf("新客户端(%d)加入成功 %s:%d \n",index,inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port));
                    }else{
                        bzero(input_msg, BUFFER_SIZE);
                        strcpy(input_msg, "服务器加入的客户端数达到最大值,无法加入!\n");
                        send(client_socket_fd, input_msg, BUFFER_SIZE, 0);
                        printf("客户端连接数达到最大值，新客户端加入失败 %s:%d \n",inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port));
                    }
                }
            }
            for (int i = 0; i <CONCURRENT_MAX; i++) {
                if (client_fds[i]!=0) {
                    if (FD_ISSET(client_fds[i], &server_fd_set)) {
                        //处理某个客户端过来的消息
                        bzero(recv_msg, BUFFER_SIZE);
                        long byte_num = recv(client_fds[i],recv_msg,BUFFER_SIZE,0);
                        if (byte_num > 0) {
                            if (byte_num > BUFFER_SIZE) {
                                byte_num = BUFFER_SIZE;
                            }
                            recv_msg[byte_num] = '\0';
                            printf("客户端(%d):%s\n",i,recv_msg);
                        }else if(byte_num < 0){
                            printf("从客户端(%d)接受消息出错.\n",i);
                        }else{
                            FD_CLR(client_fds[i], &server_fd_set);
                            client_fds[i] = 0;
                            printf("客户端(%d)退出了\n",i);
                        }
                    }
                }
            }
        }
    }
    return 0;
}


//end
