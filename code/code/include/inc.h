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
#define PORT  8899
#define ADDR  "127.0.0.1"


int readn(int s,char *buff,int len){
    int curCnt = len;
    int rc = 0;
    while(curCnt){
        rc = recv(s,buff,curCnt,0);
        if (rc == 0){
            return len - rc;
        }
        else if (rc < 0){
            return -1;
        }
        buff += rc;
        curCnt -= rc;
    }
    return len;
}


void FullAddress(sockaddr_in &sock,const std::string &addr,uint16_t port){
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    inet_pton(AF_INET,addr.c_str(),&(sock.sin_addr));
    std::cout<<"123"<<std::endl;
}
