#include"inc.h"
#include"msg.pb.h"
#define INVAILD_NUM  -1

int main(){
    struct sockaddr_in local;
	int sScoket = -1;
	int cScoket = -1;
	int ret = -1;

	local.sin_family = AF_INET;
	local.sin_port = htons( 7500 );
	local.sin_addr.s_addr = htons(INADDR_ANY);
	sScoket = Socket();
	CHECK_RET(sScoket);
	std::cout<<"$$$$$ server s = "<<sScoket<<std::endl;


	int optval = 1;
	ret = setsockopt(sScoket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	CHECK_RET(ret);

	ret = Bind(sScoket,local);
	CHECK_RET(ret);
	ret = Listen(sScoket);
	CHECK_RET(ret);

	sockaddr_in client;
	int len = sizeof(client);

	fd_set readSet;
	fd_set writeSet;
	fd_set expectSet;
	FD_ZERO(&readSet);
	FD_ZERO(&writeSet);
	FD_ZERO(&expectSet);
	FD_SET(sScoket,&readSet);
	FD_SET(sScoket,&writeSet);
	FD_SET(sScoket,&expectSet);


	std::vector<int> fdVec;
	fdVec.push_back(sScoket);
	std::vector<int> removeVec;

	while(true){
		removeVec.clear();
		for (auto v : fdVec){
			FD_SET(v,&readSet);
		}

		auto max_it = std::max_element(fdVec.begin(), fdVec.end());
		int ret = select(*max_it + 1,&readSet,&writeSet, &expectSet,0);
		CHECK_RET(ret);
		if (FD_ISSET(sScoket,&readSet)){ //有客户端连接
			cScoket = Accept(sScoket, (sockaddr*)&client, &len);
			CHECK_RET(cScoket);
			char client_ip[INET_ADDRSTRLEN] = {0};
			const char *client_ip_str = inet_ntop(AF_INET, &client.sin_addr, client_ip, INET_ADDRSTRLEN);
    		std::cout<<"Accepted connection from " << client_ip_str<< " port "<<ntohs(client.sin_port)<<std::endl;
			fdVec.push_back(cScoket);
		}
		for (auto v : fdVec)
		{
			if (FD_ISSET(v, &readSet))
			{
				char buff[1024] = {0};
				// MyMsgHead msg;
				// MyMsgHead *head;
				// int ret = recv(cScoket, buff, 1024, 0);
				{
					int n = Readn(cScoket, buff, sizeof(MsgHead));
					if (n == sizeof(MsgHead))
					{
						MsgHead *head = (MsgHead *)buff;
						if (head->msgID == eMsgType_login)
						{
							int msgLen = head->dataLen;
							n = Readn(cScoket, buff, msgLen);
							if (n == msgLen)
							{
								MyLoginMsg tmp;
								tmp.ParseFromString(buff);
								std::cout << "name= " << tmp.name() << " age= " << tmp.age() << std::endl;
							}
						}
					}
				}
				// std::cout<<"recv len "<<ret<<std::endl;
				// MyLoginMsg tem;
				// tem.ParseFromString(buff);
				// std::cout<<"test "<<tem.name()<<" age "<<tem.name()<<std::endl;
				if (ret)
				{
					// head = (MyMsgHead *)buff;
					// if (head->cmd() == eMsgType_login)
					// {
					// 	int ret = recv(cScoket, buff + sizeof(MyMsgHead), sizeof(MyLoginMsg), 0);
					// 	if (ret)
					// 	{
					// 		MyLoginMsg *msg = (MyLoginMsg *)buff;
					// 		std::cout << "recv client msg name 123 " << msg->name() << "age = " << msg->age() << std::endl;
					// 		LoginRetMsg retMsg;
					// 		retMsg.ret = 0;
					// 		retMsg.dataLen = sizeof(LoginRetMsg);
					// 		send(cScoket, (char *)&retMsg, sizeof(retMsg), 0);
					// 	}
					// }
				}
				else if (ret == 0){
					removeVec.push_back(cScoket);
					close(cScoket);
					std::cout<<"close client "<<cScoket<<std::endl;
				}
			}
		}
		for (auto v : removeVec){
			auto it = std::find_if(fdVec.begin(),fdVec.end(),[v](int temp){
				return temp == v;
			});
			fdVec.erase(it);
		}
	}



	// cScoket = Accept(sScoket, (sockaddr*)&client, &len);
	// CHECK_RET(cScoket);

	// sockaddr_in client_addr;
	// char client_ip[INET_ADDRSTRLEN] = {0};
	// const char *client_ip_str = inet_ntop(AF_INET, &client.sin_addr, client_ip, INET_ADDRSTRLEN);
    // std::cout<<"Accepted connection from " << client_ip_str<< " port "<<ntohs(client_addr.sin_port)<<std::endl;
    
	// {
	// 	char buff[1024] = {0};
	// 	MsgHead *head;
	// 	int ret = recv(cScoket,buff,sizeof(MsgHead),0);
	// 	if (ret){
	// 		head = (MsgHead*)buff;
	// 		if (head->cmd == eMsgType_login){
	// 			int ret = recv(cScoket,buff+sizeof(MsgHead),sizeof(LoginMsg),0);
	// 			if (ret){
	// 				LoginMsg *msg = (LoginMsg*)buff;
	// 				std::cout<<"recv client msg name "<<msg->name<<"age = "<<msg->age<<std::endl;
	// 				LoginRetMsg retMsg;
	// 				retMsg.ret = 0;
	// 				retMsg.dataLen = sizeof (LoginRetMsg);
	// 				send(cScoket,(char*)&retMsg,sizeof(retMsg),0);
	// 			}
	// 		}
	// 	}
		
	// }
	std::cout<<"server1 "<<std::endl;
}