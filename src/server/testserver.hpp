#include "socket.h"
#include"message.h"

class TestServer
{
public:
    TestServer() {}
    ~TestServer() {}
    static TestServer &GetIns()
    {
        static TestServer ins;
        return ins;
    }

public:
    void test_tcp();
    int process(int socketid);
};

int TestServer::process(int socketid)
{
    MSGHEAD *head;
    char buff[4096] = {0};
    std::cout<<"read fd= "<<socketid<<"data"<<std::endl;
    int n = recv(socketid, buff, sizeof(MSGHEAD), 0);
    if (n <= 0)
    {
        std::cout<<"recv error ret" <<n <<std::endl;
        return -1;
    }
    head = (MSGHEAD *)buff;
    std::cout<<"recv form client"<<head->m_cmd<<":"<<head->m_dataLen<<std::endl;
    {
        switch (head->m_cmd)
        {
        case MSGID_LOGIN:
        {
            LOGIN_MSG *msg;
            int n = recv(socketid, buff + sizeof(MSGHEAD), head->m_dataLen, 0);//MSG_DONTWAIT
            msg = (LOGIN_MSG*)buff;
            std::cout << "recv login msg " << msg->name << ":" << msg->age << std::endl;

            LOGIN_MSG_ACK msgAck;
            msgAck.ret = 100;
            send(socketid,(char*)&msgAck,sizeof(LOGIN_MSG_ACK),0);
        }
        break;
        default:
        {
            close(socketid);
            return -1;
        }
        break;
        }
    }
    return 0;
}

void TestServer::test_tcp()
{
    std::cout << "====test_tcp======" << std::endl;
    int listenfd = 0, clientfd = 0,maxfd = 0;
    sockaddr_in serverInfo, clientInfo;
    socklen_t len = sizeof(serverInfo);
    char sendBuff[MAXLINE] = {0}, recvBuff[MAXLINE] = {0};
    std::vector<int> clients;
    int n = 0;

    listenfd = SocketAPI::GetInstance().Socket(AF_INET, SOCK_STREAM);
    memset(&serverInfo, 0, sizeof(serverInfo));
    SocketAPI::GetInstance().FullAddr(serverInfo);
    SocketAPI::GetInstance().Bind(listenfd, serverInfo, len);
    SocketAPI::GetInstance().Listen(listenfd, 5);

    maxfd = listenfd;
    fd_set rSet;
    for (;;)
    {
        FD_ZERO(&rSet);
        FD_SET(listenfd, &rSet);

        for (auto v : clients)
        {
            FD_SET(v,&rSet);
        }

        std::cout<<"select zuse 0 "<<std::endl;
        if ((n = select(maxfd + 1, &rSet, NULL, NULL, NULL)) == -1)
        {
            std::cout << "select error" << std::endl;
        }

        if (FD_ISSET(listenfd, &rSet))
        {
            clientfd = SocketAPI::GetInstance().Accept(listenfd, clientInfo, len);
            if (clientfd)
            {
                maxfd = maxfd > clientfd ? maxfd : clientfd;
                clients.push_back(clientfd);
            }
        }
        else
        {
            for (auto v : clients)
            {
                if (FD_ISSET(v, &rSet))
                {
                    std::cout<<"socket "<<v<< "is set"<<std::endl;
                    if (process(v) == -1)
                    {
                        auto it = std::find(clients.begin(),clients.end(),v);
                        if (it != clients.end())
                            clients.erase(it);
                    }
                }
            }
        }
    }
    close(listenfd);
}
