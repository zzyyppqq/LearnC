//
// Created by 张宜鹏 on 2022/8/11.
//

/**
 * BSD Socket编程详解
 * https://blog.csdn.net/auspark/article/details/105049667
 * 使用kqueue Mac是基于BSD的内核
 * 所使用的是kqueue（kernel event notification mechanism，详细内容可以Mac中 man 2 kqueue），
 * kqueue比select先进的地方就在于使用事件触发的机制，且其调用无需每次对所有的文件描述符进行遍历，
 * 返回的时候只返回需要处理的事件，而不像select中需要自己去一个个通过FD_ISSET检查。 kqueue默认的触发方式是level 水平触发，
 * 可以通过设置event的flag为EV_CLEAR 使得这个事件变为边沿触发,可能epoll的触发方式无法细化到单个event，需要查证。
 * kqueue中涉及两个系统调用，kqueue()和kevent()
 *
 * kqueue() 创建kernel级别的事件队列，并返回队列的文件描述符
 * kevent() 往事件队列中加入订阅事件，或者返回相关的事件数组 kqueue使用的流程一般如下：
 * 创建kqueue
 * 创建struct kevent变量（注意这里的kevent是结构体类型名），可以通过EV_SET这个宏提供的快捷方式进行创建
 * 通过kevent系统调用将创建好的kevent结构体变量加入到kqueue队列中，完成对指定文件描述符的事件的订阅
 * 通过kevent系统调用获取满足条件的事件队列，并对每一个事件进行处理
 */
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#define BACKLOG 5 //完成三次握手但没有accept的队列的长度
#define CONCURRENT_MAX 8 //应用层同时可以处理的连接
#define SERVER_PORT 11332
#define BUFFER_SIZE 1024
#define QUIT_CMD ".quit"
int client_fds[CONCURRENT_MAX];
struct kevent events[10];//CONCURRENT_MAX + 2
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
    struct timespec timeout = {10,0};
    //kqueue
    int kq = kqueue();
    if (kq == -1) {
        perror("创建kqueue出错!\n");
        exit(1);
    }
    struct kevent event_change;
    EV_SET(&event_change, STDIN_FILENO, EVFILT_READ, EV_ADD, 0, 0, NULL);
    kevent(kq, &event_change, 1, NULL, 0, NULL);
    EV_SET(&event_change, server_sock_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
    kevent(kq, &event_change, 1, NULL, 0, NULL);
    while (1) {
        int ret = kevent(kq, NULL, 0, events, 10, &timeout);
        if (ret < 0) {
            printf("kevent 出错!\n");
            continue;
        }else if(ret == 0){
            printf("kenvent 超时!\n");
            continue;
        }else{
            //ret > 0 返回事件放在events中
            for (int i = 0; i < ret; i++) {
                struct kevent current_event = events[i];
                //kevent中的ident就是文件描述符
                if (current_event.ident == STDIN_FILENO) {
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
                }else if(current_event.ident == server_sock_fd){
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
                            EV_SET(&event_change, client_socket_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
                            kevent(kq, &event_change, 1, NULL, 0, NULL);
                            printf("新客户端(fd = %d)加入成功 %s:%d \n",client_socket_fd,inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port));
                        }else{
                            bzero(input_msg, BUFFER_SIZE);
                            strcpy(input_msg, "服务器加入的客户端数达到最大值,无法加入!\n");
                            send(client_socket_fd, input_msg, BUFFER_SIZE, 0);
                            printf("客户端连接数达到最大值，新客户端加入失败 %s:%d \n",inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port));
                        }
                    }
                }else{
                    //处理某个客户端过来的消息
                    bzero(recv_msg, BUFFER_SIZE);
                    long byte_num = recv((int)current_event.ident,recv_msg,BUFFER_SIZE,0);
                    if (byte_num > 0) {
                        if (byte_num > BUFFER_SIZE) {
                            byte_num = BUFFER_SIZE;
                        }
                        recv_msg[byte_num] = '\0';
                        printf("客户端(fd = %d):%s\n",(int)current_event.ident,recv_msg);
                    }else if(byte_num < 0){
                        printf("从客户端(fd = %d)接受消息出错.\n",(int)current_event.ident);
                    }else{
                        EV_SET(&event_change, current_event.ident, EVFILT_READ, EV_DELETE, 0, 0, NULL);
                        kevent(kq, &event_change, 1, NULL, 0, NULL);
                        close((int)current_event.ident);
                        for (int i = 0; i < CONCURRENT_MAX; i++) {
                            if (client_fds[i] == (int)current_event.ident) {
                                client_fds[i] = 0;
                                break;
                            }
                        }
                        printf("客户端(fd = %d)退出了\n",(int)current_event.ident);
                    }
                }
            }
        }
    }
    return 0;
}


//end


