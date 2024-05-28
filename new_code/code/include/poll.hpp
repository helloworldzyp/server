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
				ret = HandMsg(cScoket);
				if (ret == 0){
					removeVec.push_back(cScoket);
					close(cScoket);
					std::cout<<"close client "<<cScoket<<std::endl;
				}
			}
		}
		for (auto v : removeVec){
			auto it = std::find_if(m_csvec.begin(),m_csvec.end(),[v](int temp){
				return temp == v;
			});
			m_csvec.erase(it);
		}
	}
}




