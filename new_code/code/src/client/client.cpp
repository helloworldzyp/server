#include"buildmsg.hpp"
#include"reg.hpp"
#include"msg.pb.h"

int main(){
	init();
    struct sockaddr_in peer;
	int s;
	int rc;
	char buf[ 1 ];

	peer.sin_family = AF_INET;
	peer.sin_port = htons( 7500 );
	peer.sin_addr.s_addr = inet_addr( "127.0.0.1" );

	s = Socket();
	std::cout<<"$$$$$ client s = "<<s<<std::endl;
	CHECK_RET(s);
	rc = Connect(s,peer);
	std::cout<<"$$$$$ client s1 = "<<s<<std::endl;
	CHECK_RET(rc);

	std::string sendStr = BuildLoginMsg("test",99);
	int ret  = send(s,sendStr.c_str(),sendStr.size(),0);
    std::cout<<"client send len="<<ret<<std::endl;
	sendStr = BuildChatMsg("this is chat msg");
	ret  = send(s,sendStr.c_str(),sendStr.size(),0);
    std::cout<<"client send len="<<ret<<std::endl;
}