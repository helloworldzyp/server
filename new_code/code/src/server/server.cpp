#include"buildmsg.hpp"
#include"reg.hpp"
#include"poll.hpp"

#define INVAILD_NUM  -1

int main(){
	init();
    struct sockaddr_in local;
	int sScoket = -1;
	int cScoket = -1;
	int ret = -1;

	local.sin_family = AF_INET;
	local.sin_port = htons( 7500 );
	local.sin_addr.s_addr = inet_addr("172.23.54.36");//htons(INADDR_ANY);
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

	// Select sel(sScoket);
	// sel.Update();

	Epoll po(sScoket);
	po.Update();

	std::cout<<"server1 "<<std::endl;
}