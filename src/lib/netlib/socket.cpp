#include "socket.h"
using namespace std;

int SocketAPI::Socket(int family, int proto)
{
    int fd = socket(family, proto, 0);
    if (fd < 0)
    {
        cout << "socket error" << endl;
        exit(-1);
    }
    return fd;
}

int SocketAPI::Close(int socket)
{
    int ret = close(socket);
    if (ret < 0)
    {
        cout << "close error" << endl;
        exit(-1);
    }
    return ret;
}

int SocketAPI::Bind(int socketfd, sockaddr_in &addr, socklen_t &len)
{
    int ret = bind(socketfd, (const struct sockaddr *)&addr, len);
    if (ret < 0)
    {
        cout << "bind error" << endl;
        exit(-1);
    }
    return ret;
}

int SocketAPI::Listen(int socketfd, int block)
{
    int ret = listen(socketfd, block);
    if (ret < 0)
    {
        cout << "listen error" << endl;
        exit(-1);
    }
    return ret;
}

int SocketAPI::Accept(int socketfd, sockaddr_in &addr, socklen_t &len)
{
    int connfd = accept(socketfd, (sockaddr *)&addr, &len);
    if (connfd < 0)
    {
        cout << "connfd error" << endl;
        exit(-1);
    }
    char buff[MAXLINE] = {0};
    cout << "client form ip:" << inet_ntop(AF_INET, &addr.sin_addr, buff, sizeof(buff)) << "  port:" << ntohs(addr.sin_port) << endl;
    return connfd;
}

int SocketAPI::Connect(int socketfd, sockaddr_in &addr, socklen_t &len)
{
    int ret = connect(socketfd, (const struct sockaddr *)&addr, len);
    if (ret < 0)
    {
        cout << "bind error" << endl;
        exit(-1);
    }
    return ret;
}

void SocketAPI::FullAddr(sockaddr_in &addr)
{
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &addr.sin_addr);
}

