#pragma once
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <fcntl.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <poll.h>
#include<thread>
#define MAXLINE 1024
#define IP "127.0.0.1"
#define PORT 8899


class SocketAPI
{
public:
    SocketAPI() {}
    ~SocketAPI() {}
    static SocketAPI &GetInstance(){
        static SocketAPI ins;
        return ins;
    }

public:
    int Socket(int family, int protol);
    int Bind(int socketfd, sockaddr_in &addr, socklen_t &len);
    int Listen(int socketfd, int block);
    int Accept(int socketfd, sockaddr_in &addr, socklen_t &len);
    int Connect(int socketfd, sockaddr_in &addr, socklen_t &len);
    int Close(int socket);
    void FullAddr(sockaddr_in &addr);
};
