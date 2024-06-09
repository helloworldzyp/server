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

void HandleMutilChat(const void *buf, int len){
    MutilChatMsg *msg = (MutilChatMsg*)buf;
    std::string tempStr;
    for (int i = 0; i < msg->chat_size(); i++){
       tempStr.append(msg->chat(i)).append("  ");
    }
    std::cout<<"HandleMutilChat str = "<<tempStr<<std::endl;
}


///////////////////////////////////////////////////////////////////

//注册消息函数
void RegFunc(uint32_t msgID, ::google::protobuf::Message *message, HandleFunc func){
    CmdMessageInfo *msgInfo = new CmdMessageInfo;
    msgInfo->pFunc = func;
    msgInfo->pMessage = message;
    g_commandMap[msgID] = msgInfo;
}

void initRegMsg(){
    RegFunc(eMsgType_login,new MyLoginMsg,HandleLogin);
    RegFunc(eMsgType_chat,new ChatMsg,HandleChat);
    RegFunc(eMsgType_mutil_chat,new MutilChatMsg,HandleMutilChat);
}

//统一消息处理入口
void HandMsg(uint32_t msgID,std::string buf){
    auto it = g_commandMap.find(msgID);
    if (it != g_commandMap.end()){
        it->second->pMessage->ParseFromString(buf);
        it->second->pFunc(it->second->pMessage,0);       
    }
}

void HandMsg(uint32_t msgID,char* buf){
    auto it = g_commandMap.find(msgID);
    if (it != g_commandMap.end()){
        it->second->pMessage->ParseFromString(buf);
        it->second->pFunc(it->second->pMessage,0);       
    }
}

int HandMsg(int cScoket){
    std::cout<<"handle msg client id = "<<cScoket<<std::endl;
    char buff[64 * 1024] = {0};
    int ret = Readn(cScoket, buff, sizeof(MsgHead));
    if (ret == g_headMsgSize){
        MsgHead *head = (MsgHead *)buff;
        int tmpMsgLen = head->dataLen;
        int tmpMsgID = head->msgID;{
            memset(buff, 0, sizeof(buff));
            ret = Readn(cScoket, buff, tmpMsgLen);
            if (ret == tmpMsgLen){
                HandMsg(tmpMsgID, buff);
            }
        }
    }
    return ret;
}

::google::protobuf::Message* CreateMeaage(std::string msgName){
    using namespace ::google::protobuf;
    Message* message = nullptr;
    const Descriptor *des = DescriptorPool::generated_pool()->FindMessageTypeByName(msgName);
    if (des){
        const Message* protoType = MessageFactory::generated_factory()->GetPrototype(des);
        if (protoType){
            message = protoType->New();
        }
    }
    return message;
}


void testProtobuf()
{
    ::google::protobuf::Message* message = CreateMeaage("ChatMsg");
    std::cout<<message<<std::endl;
}