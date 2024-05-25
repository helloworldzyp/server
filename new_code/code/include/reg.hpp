#pragma once
#include"inc.h"

typedef std::function<void(const void *buf, int len)> HandleFunc;
typedef struct tagCmdMessageInfo{
    HandleFunc pFunc;
    ::google::protobuf::Message *pMessage;
} CmdMessageInfo, *PCmdMessageInfo;
typedef std::map<uint32_t, PCmdMessageInfo> commandMap;
commandMap g_commandMap;

///////////////////////////handle msg///////////////////////////////
void HandleLogin(const void *buf, int len){
    MyLoginMsg *msg = (MyLoginMsg*)buf;
    std::cout<<"name is:"<<msg->name()<<" age is:"<<msg->age()<<std::endl;
}

void HandleChat(const void *buf, int len){
    ChatMsg *msg = (ChatMsg*)buf;
    std::cout<<"chat msg is:"<<msg->chat()<<std::endl;
}
///////////////////////////////////////////////////////////////////

//注册消息函数
void RegFunc(uint32_t msgID, ::google::protobuf::Message *message, HandleFunc func){
    CmdMessageInfo *msgInfo = new CmdMessageInfo;
    msgInfo->pFunc = func;
    msgInfo->pMessage = message;
    g_commandMap[msgID] = msgInfo;
}

void init(){
    RegFunc(eMsgType_login,new MyLoginMsg,HandleLogin);
    RegFunc(eMsgType_chat,new ChatMsg,HandleChat);
}

//统一消息处理入口
void HandMsg(uint32_t msgID,std::string buf){
    auto it = g_commandMap.find(msgID);
    if (it != g_commandMap.end()){
        it->second->pMessage->ParseFromString(buf);
        it->second->pFunc(it->second->pMessage,0);       
    }
}


