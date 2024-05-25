#pragma once
#include<iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
 
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>
#include<string>
#include<vector>
#include <algorithm>
#include"msg.pb.h"

#define CHECK_RET(x) if (x < 0) exit(1)

///////////////////////proto //////////////
struct MsgHead{
    int dataLen;
    int msgID;
};

enum MsgType{
    eMsgType_login,
    eMsgType_login_ret,
};


void FullAddress(sockaddr_in &addr,std::string ip,uint16_t port){
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_pton(AF_INET,ip.c_str(),&addr.sin_addr);
    addr.sin_port = htons(port);
}

int Socket(){
    auto s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (s < 0){
        std::cout<<"socket error"<<std::endl;
    }
    return s;
}

int Bind(int soc, sockaddr_in addr){
    int ret = bind(soc,reinterpret_cast<sockaddr*>(&addr),sizeof(sockaddr));
    if (ret < 0){
         std::cout<<"bind error"<<std::endl;
    }
    return ret;
}

int Listen(int soc){
    int ret = listen(soc,5);
    if (ret < 0){
         std::cout<<"listen error"<<std::endl;
    }
    return ret;
}

int Accept(int soc,sockaddr *peer,int* len){
    int ret = accept(soc,peer,(socklen_t*)len);
    if (ret < 0){
         std::cout<<"accept error"<<std::endl;
    }
    return ret;
}

int Connect(int soc,sockaddr_in addr){
    int ret = connect(soc,(sockaddr*)&addr,sizeof(sockaddr));
    if (ret < 0){
         std::cout<<"connet error"<<std::endl;
    }
    return ret;
}

// 从文件描述符fd中读取n字节到缓冲区buf中
ssize_t Readn(int fd, void *buf, size_t n) {
    size_t nleft = n;       // 剩余的字节数
    ssize_t nread;          // 实际读取到的字节数
    char *ptr = (char*)buf; // 缓冲区指针

    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR) {
                nread = 0;   // 被信号中断，重新读取
            } else {
                return -1;   // 读取错误
            }
        } else if (nread == 0) {
            break;           // EOF
        }

        nleft -= nread;
        ptr += nread;
    }

    return (n - nleft);      // 返回实际读取的字节数
}

// 将n字节的数据从缓冲区buf写入文件描述符fd中
ssize_t Writen(int fd, const void *buf, size_t n) {
    size_t nleft = n;          // 剩余的字节数
    ssize_t nwritten;          // 实际写入的字节数
    const char *ptr = (const char*)buf; // 缓冲区指针

    while (nleft > 0) {
        if ((nwritten = write(fd, ptr, nleft)) <= 0) {
            if (nwritten < 0 && errno == EINTR) {
                nwritten = 0;   // 被信号中断，重新写入
            } else {
                return -1;      // 写入错误
            }
        }

        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}

char g_sendBuf[64 * 1024] = {0};

void BuildMsgHead(int msgID,int len){
    MsgHead *head = (MsgHead*)g_sendBuf;
    head->dataLen = len;
    head->msgID = msgID;
}

std::string BuildLoginMsg(std::string name, uint16_t age){
    MyLoginMsg loginMsg;
    loginMsg.set_name(name);
    loginMsg.set_age(age);
    std::string sendStr = loginMsg.SerializeAsString();
    BuildMsgHead(eMsgType_login,sendStr.size());
    return std::string(g_sendBuf,sizeof(MsgHead)) + sendStr;
}


