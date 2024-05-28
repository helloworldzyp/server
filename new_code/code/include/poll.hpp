#pragma once
#include"reg.hpp"
#include"inc.h"

class noncopyable
{
 public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

 protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

// sockaddr_in client;
// 	int len = sizeof(client);

// 	fd_set readSet;
// 	fd_set writeSet;
// 	fd_set expectSet;
// 	FD_ZERO(&readSet);
// 	FD_ZERO(&writeSet);
// 	FD_ZERO(&expectSet);
// 	FD_SET(sScoket,&readSet);
// 	FD_SET(sScoket,&writeSet);
// 	FD_SET(sScoket,&expectSet);


// 	std::vector<int> fdVec;
// 	fdVec.push_back(sScoket);
// 	std::vector<int> removeVec;

// 	while(true){
// 		removeVec.clear();
// 		for (auto v : fdVec){
// 			FD_SET(v,&readSet);
// 		}

// 		auto max_it = std::max_element(fdVec.begin(), fdVec.end());
// 		int ret = select(*max_it + 1,&readSet,&writeSet, &expectSet,0);
// 		CHECK_RET(ret);
// 		if (FD_ISSET(sScoket,&readSet)){ //有客户端连接
// 			cScoket = Accept(sScoket, (sockaddr*)&client, &len);
// 			CHECK_RET(cScoket);
// 			char client_ip[INET_ADDRSTRLEN] = {0};
// 			const char *client_ip_str = inet_ntop(AF_INET, &client.sin_addr, client_ip, INET_ADDRSTRLEN);
//     		std::cout<<"Accepted connection from " << client_ip_str<< " port "<<ntohs(client.sin_port)<<std::endl;
// 			fdVec.push_back(cScoket);
// 		}
// 		for (auto v : fdVec){
// 			if (FD_ISSET(v, &readSet)){
// 				ret = HandMsg(cScoket);
// 				if (ret == 0){
// 					removeVec.push_back(cScoket);
// 					close(cScoket);
// 					std::cout<<"close client "<<cScoket<<std::endl;
// 				}
// 			}
// 		}
// 		for (auto v : removeVec){
// 			auto it = std::find_if(fdVec.begin(),fdVec.end(),[v](int temp){
// 				return temp == v;
// 			});
// 			fdVec.erase(it);
// 		}
// 	}

class Poller : public noncopyable
{
    public:
        Poller(){}
        ~Poller(){}
        virtual void Update() = 0;
   
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
		int ret = select(*max_it + 1,&readSet,nullptr,nullptr,0);
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

    typedef std::vector<struct epoll_event> EventList;
    EventList events_;

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
      
        int nfds = epoll_wait(epoll_fd, events, 100, -1);
        if (nfds < 0) {
            perror("epoll_wait error");
            break;
        }

        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == m_socket) {
                if ((new_socket = accept(m_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                    perror("accept");
                    continue;
                }
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
                int client_fd = events[i].data.fd;
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


