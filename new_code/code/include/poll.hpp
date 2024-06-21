#pragma once
#include"reg.hpp"
#include"inc.h"
#include<map>
#include<vector>
#include<functional>

class noncopyable
{
 public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

 protected:
  noncopyable() = default;
  ~noncopyable() = default;
};



void test_getsockname(int socketid,int clientid){
    struct sockaddr_in server_local_addr;
    socklen_t server_local_addr_len = sizeof(server_local_addr);
    getsockname(socketid, (struct sockaddr*)&server_local_addr, &server_local_addr_len);
    std::cout << "服务器本地地址和端口: " << inet_ntoa(server_local_addr.sin_addr) << ":" << ntohs(server_local_addr.sin_port) << std::endl;

    // 获取客户端套接字的远程对等体地址和端口
    struct sockaddr_in client_peer_addr;
    socklen_t client_peer_addr_len = sizeof(client_peer_addr);
    getpeername(clientid, (struct sockaddr*)&client_peer_addr, &client_peer_addr_len);
    std::cout << "客户端远程对等体地址和端口: " << inet_ntoa(client_peer_addr.sin_addr) << ":" << ntohs(client_peer_addr.sin_port) << std::endl;

}

class Poller : public noncopyable
{
    public:
        Poller(){}
        ~Poller(){}
        virtual void Update(){std::cout<<"not complete"<<std::endl;};
};

class Select : public Poller
{
    public:
        Select(int s){
            m_socket = s;
        }
        ~Select(){}
    public:
        void Update();
    private:
        std::vector<int> m_csvec;
        int m_socket = -1;
};

class Epoll : public Poller
{
    public:
        Epoll(int s){
            m_socket = s;
        }
        ~Epoll(){}
    public:
        void Update();
    private:
        std::vector<int> m_csvec;
        int m_socket = -1;
};



void Select::Update()
{
    std::cout<<"this is select update"<<std::endl;
    sockaddr_in client;
	int len = sizeof(client);
    int cScoket = 0;
	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET(m_socket,&readSet);

	std::vector<int> removeVec;
	m_csvec.push_back(m_socket);

	while(true){
		removeVec.clear();
		for (auto v : m_csvec){
			FD_SET(v,&readSet);
		}

		auto max_it = std::max_element(m_csvec.begin(), m_csvec.end());
		int ret = select(*max_it + 1,&readSet,nullptr,nullptr,0); //(立即返回)   //永远等待下去：设为空指针  等待一段固定时间 立即返回(轮询)：timeval结构中的时间设为0
		CHECK_RET(ret);
		if (FD_ISSET(m_socket,&readSet)){ //有客户端连接
			cScoket = Accept(m_socket, (sockaddr*)&client, &len);
			CHECK_RET(cScoket);
			char client_ip[INET_ADDRSTRLEN] = {0};
			const char *client_ip_str = inet_ntop(AF_INET, &client.sin_addr, client_ip, INET_ADDRSTRLEN);
    		std::cout<<"Accepted connection from " << client_ip_str<< " port "<<ntohs(client.sin_port)<<std::endl;
			m_csvec.push_back(cScoket);
		}
		for (auto v : m_csvec){
			if (FD_ISSET(v, &readSet)){
				ret = HandMsg(v);
				if (ret == 0){
					removeVec.push_back(v);
					close(v);
					std::cout<<"close client "<<v<<std::endl;
				}
			}
		}
        std::cout<<"client size = "<<m_csvec.size()<<std::endl;
		for (auto v : removeVec){
			auto it = std::find_if(m_csvec.begin(),m_csvec.end(),[v](int temp){
				return temp == v;
			});
			m_csvec.erase(it);
		}
	}
}

void Epoll::Update()
{
    std::cout<<"this is epoll update"<<std::endl;
    typedef std::vector<struct epoll_event> EventList;
    EventList events_(1000);

    struct epoll_event events[1024];
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int epoll_fd,new_socket;
    // std::vector<epoll_event> events;
    struct epoll_event ev;

    if ((epoll_fd = epoll_create1(0)) < 0) {
        perror("epoll_create1 failed");
        close(m_socket);
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = m_socket;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, m_socket, &ev) < 0) {
        perror("epoll_ctl failed");
        close(m_socket);
        close(epoll_fd);
        exit(EXIT_FAILURE);
    }

    while (true) {
      
        // int nfds = epoll_wait(epoll_fd, events, 100, -1);
        int nfds = epoll_wait(epoll_fd,&*events_.begin(),events_.size(),-1);
        if (nfds < 0) {
            perror("epoll_wait error");
            break;
        }
        std::cout<<"$$$$ size "<<nfds<<std::endl;

        for (int i = 0; i < nfds; i++) {
            if (events_[i].data.fd == m_socket) {
                if ((new_socket = accept(m_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                    perror("accept");
                    continue;
                }
                test_getsockname(m_socket,new_socket);
                char client_ip[INET_ADDRSTRLEN] = {0};
			    const char *client_ip_str = inet_ntop(AF_INET, &address.sin_addr, client_ip, INET_ADDRSTRLEN);
    		    std::cout<<"Accepted connection from " << client_ip_str<< " port "<<ntohs(address.sin_port)<<std::endl;
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = new_socket;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_socket, &ev) < 0) {
                    perror("epoll_ctl: new_socket");
                    close(new_socket);
                    continue;
                }
            } else {
                int client_fd = events_[i].data.fd;
                int ret = HandMsg(client_fd);
                if (ret == -1 || ret == 0){
                    close(client_fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, NULL);
                }
            }
        }
    }

    close(m_socket);
    close(epoll_fd);

}

typedef std::function<void()> CommonFunc;
template<typename F, typename... A>
CommonFunc FuncPackage(F f, A... argc) {
	using FuncType = decltype(f(argc...));
	auto tempFunc = std::bind(std::forward<F>(f), std::forward<A>(argc)...);
	return tempFunc;
}

class EpollHelper : public Poller{
    struct IO_EVENT{
         int event;
         CommonFunc readFunc;
         CommonFunc writeFunc;
    };
    public:
        EpollHelper() : m_poll_fd(epoll_create1(EPOLL_CLOEXEC)),m_poll_events(1024){}
        ~EpollHelper(){close(m_poll_fd);}
    public:
        void AddFD(int fd,int event,const CommonFunc& cb);
        void DelFD(int fd);
        void Update();
        void HandleIO(int cn);
    private:
        bool m_stop = false;
        int m_poll_fd = -1;
        std::map<int,IO_EVENT> m_io_events;    //fd ---> events
        std::vector<epoll_event> m_poll_events; //for epoll_wait use
};

void EpollHelper::AddFD(int fd,int event,const CommonFunc& cb){
    auto &events = m_io_events[fd];
    int tempEvent = event | events.event;
    int op = events.event == 0 ? EPOLL_CTL_ADD : EPOLL_CTL_MOD;
    if (event & EPOLLIN){
        events.readFunc = cb;
    }
    else if (event & EPOLLOUT){
        events.writeFunc = cb;        
    }
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = tempEvent;
    int ret = epoll_ctl(m_poll_fd,op,fd,&ev);
    if (-1 == ret){
        std::cout<<"AddFD error"<<std::endl;
    }
}

void EpollHelper::DelFD(int fd){
    m_io_events.erase(fd);
    int ret = epoll_ctl(m_poll_fd,EPOLL_CTL_DEL,fd,nullptr);
    if (-1 == ret){
        std::cout<<"DelFD error"<<std::endl;
    }
}

void EpollHelper::HandleIO(int cn){
    for (int i = 0; i < cn; i++){
        epoll_event ev = m_poll_events[i];
        auto it = m_io_events.find(ev.data.fd);
        if (it != m_io_events.end()){
            if (ev.events & EPOLLIN){
                it->second.readFunc();
            }
            else if (ev.events & EPOLLIN){
                it->second.writeFunc();
            }
            else{
                DelFD(ev.data.fd);
            }
        }
    }
}

void EpollHelper::Update(){
    while(!m_stop){
        int cn = epoll_wait(m_poll_fd,&*m_poll_events.begin(),m_poll_events.size(),-1);
        if (cn > 0){
            std::cout<<"handle io "<<cn<<std::endl;
            HandleIO(cn);
        }
    }
}

void HandleMsg(int sockfd){
    int ret = HandMsg(sockfd);
    if (ret == -1 || ret == 0){
        close(sockfd);
    }
}

void HandleAccept(int sockfd,EpollHelper* epoller){
    std::cout<<"handle accept"<<std::endl;
    int new_socket = -1;
    sockaddr_in address;
    int addrlen = sizeof(sockaddr_in);
    if ((new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0){
        perror("accept");
    }
    test_getsockname(sockfd, new_socket);
    char client_ip[INET_ADDRSTRLEN] = {0};
    const char *client_ip_str = inet_ntop(AF_INET, &address.sin_addr, client_ip, INET_ADDRSTRLEN);
    std::cout << "Accepted connection from " << client_ip_str << " port " << ntohs(address.sin_port) << std::endl;

    auto func = FuncPackage(HandleMsg,new_socket);
    epoller->AddFD(new_socket,EPOLLIN,func);
}

