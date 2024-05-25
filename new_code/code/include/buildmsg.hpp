#pragma once
#include"inc.h"

///////////////////////proto //////////////
struct MsgHead{
    int dataLen;
    int msgID;
};

enum MsgType{
    eMsgType_login = 1000,
    eMsgType_login_ret,
    eMsgType_chat,
};

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

std::string BuildChatMsg(std::string chat){
    ChatMsg msg;
    msg.set_chat(chat);
    std::string sendStr = msg.SerializeAsString();
    BuildMsgHead(eMsgType_chat,sendStr.size());
    return std::string(g_sendBuf,sizeof(MsgHead)) + sendStr;
}