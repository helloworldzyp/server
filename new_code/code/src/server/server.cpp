#include"buildmsg.hpp"
#include"reg.hpp"
#include"poll.hpp"

#define INVAILD_NUM  -1

class Server{
	public:
		Server(std::string strIP,int port,bool isepoll):m_str_ip(strIP),m_port(port){
			initRegMsg();
			init();
			if (isepoll){
				// m_poll = new Epoll(m_socket);
				m_poll = new EpollHelper();
			}
			else{
				m_poll = new Select(m_socket);
			}
		};
		~Server() = default;
	public:
		void init();
		void start();
	private:
		std::string m_str_ip = "0.0.0.0";
		int m_port = 7500;
		int m_socket = -1;
		Poller *m_poll = nullptr;
};

void Server::init(){
    struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons( m_port );
	local.sin_addr.s_addr = inet_addr(m_str_ip.data());//htons(INADDR_ANY);
	m_socket = Socket();
	int optval = 1;
	int ret = setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	CHECK_RET(ret);
	ret = Bind(m_socket,local);
	CHECK_RET(ret);
	ret = Listen(m_socket);
	CHECK_RET(ret);
	
}

void Server::start(){
	auto func = FuncPackage(HandleAccept,m_socket,(EpollHelper*)m_poll);
	((EpollHelper*)m_poll)->AddFD(m_socket,EPOLLIN,func);
	m_poll->Update();
}

int main(){
	Server s("0.0.0.0",7500,true);
	s.start();
}