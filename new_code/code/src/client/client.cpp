#include"buildmsg.hpp"
#include"reg.hpp"
#include"msg.pb.h"

class Client{
	public:
		Client(std::string strIP,int port):m_str_ip(strIP),m_port(port){
			initRegMsg();
			init();
		};
		~Client(){close(m_soketid);};
	public:
		void init();
		void start();
	private:
		int m_thread_count = 1;
		std::string m_str_ip = "127.0.0.1";
		int m_port = 7500;
		int m_soketid = -1;
};

void Client::init(){
	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(m_port);
	peer.sin_addr.s_addr = inet_addr(m_str_ip.c_str());
	m_soketid = Socket();
	Connect(m_soketid,peer);
}

void Client::start(){
	for (int i = 0; i < 1; i++){
		std::string sendStr = BuildLoginMsg("test", 99);
		int ret = send(m_soketid, sendStr.c_str(), sendStr.size(), 0);

		sendStr = BuildChatMsg("this is chat msg");
		ret = send(m_soketid, sendStr.c_str(), sendStr.size(), 0);
		std::cout << "i = " << i << std::endl;
		
		std::vector<std::string> mutilChat = {"123", "test", "asd"};
		sendStr = BuildMutilChatMsg(mutilChat);
		ret = send(m_soketid, sendStr.c_str(), sendStr.size(), 0);
		sleep(2);
	}
}


void test_func(){
	Client c("127.0.0.1",7500);
	c.start();
}

int main(){
	for (int i = 0; i < 1; i++){
		test_func();
	}
}
