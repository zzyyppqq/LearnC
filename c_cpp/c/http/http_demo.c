//
// Created by zhangyipeng on 2023/11/7.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../libs/string_builder.h"


int main() {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    portno = 80;  // HTTP 默认端口号

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname("www.example.com"); // 目标主机的域名或 IP 地址
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    // 构造 HTTP 请求
    sprintf(buffer, "GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n");

    // 发送 HTTP 请求
    n = send(sockfd, buffer, strlen(buffer), 0);
    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

    StringBuilder sb;
    StringBuilder_init(&sb);

    // 读取响应
    bzero(buffer, 256);
    while ((n = recv(sockfd, buffer, 255, 0)) > 0) {
//        printf("%s", buffer);
        StringBuilder_append(&sb, buffer);
        printf("n: %d\n",n);
        if (n < 255) {
            break;
        }
        bzero(buffer, 256);
    }
    printf("%s\n", sb.buffer);
    StringBuilder_free(&sb);

    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }

    //close(sockfd);
    int ret = shutdown(sockfd, SHUT_RD); // 关闭连接的读取端
    if (ret == -1) {
        perror("shutdown error");
    } else {
        printf("连接的读取端已关闭\n");
    }
    return 0;
}
