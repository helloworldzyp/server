#include"buildmsg.hpp"
#include"reg.hpp"
#define INVAILD_NUM  -1

int main(){
	init();
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
		for (auto v : fdVec){
			if (FD_ISSET(v, &readSet)){
				char buff[64 * 1024] = {0};
				int ret = Readn(cScoket, buff, sizeof(MsgHead));
				if (ret == sizeof(MsgHead)){
					MsgHead *head = (MsgHead *)buff;
					int tmpMsgLen = head->dataLen;
					int tmpMsgID = head->msgID;{
						ret = Readn(cScoket, buff, tmpMsgLen);
						if (ret == tmpMsgLen){
							HandMsg(tmpMsgID, buff);
						}
					}
				}
				if (ret == 0){
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
	std::cout<<"server1 "<<std::endl;
}