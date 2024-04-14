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

#define CHECK_RET(x) if (x < 0) exit(1)


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



///////////////////////proto //////////////

struct MsgHead{
    int dataLen;
    int cmd;
};

enum MsgType{
    eMsgType_login,
    eMsgType_login_ret,
};

struct LoginMsg : public MsgHead{
    LoginMsg(){
        age = 0;
        cmd =  eMsgType_login;
    }
    char name[125];
    int age;
};

struct LoginRetMsg : public MsgHead{
    LoginRetMsg(){
        ret = 0;
        cmd = eMsgType_login_ret;
    }
    int ret;
};