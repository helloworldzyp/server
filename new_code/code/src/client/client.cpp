#include"inc.h"
#include"msg.pb.h"


int main(){

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

	// LoginMsg msg;
	// msg.age = 2;
	// strcpy(msg.name,"qiqi");
	// msg.dataLen = sizeof(msg);
	MyLoginMsg msg;
	auto haed = msg.mutable_head();
	haed->set_cmd(123);
	msg.set_age(1);
	msg.set_name("123");
	std::string sendStr = msg.SerializeAsString();
	std::cout<<"sizeof(logingMsg)="<<sizeof(MyLoginMsg)<<std::endl;
	std::cout<<"sizeof(sendStr)="<<sendStr.size()<<std::endl;

	// int realLen = sizeof(MyLoginMsg) - sizeof(MyMsgHead);
	// std::cout<<"send msg real length "<<realLen<<std::endl;
	// head->set_datalen(realLen);

	// char buff[1024] = {0};
	// {

	// 	strcpy(buff,sendStr.data());
	// 	MyLoginMsg tem;
	// 	tem.ParseFromString(buff);
	// 	std::cout<<"test "<<tem.name()<<" age "<<tem.head().cmd()<<std::endl;
	// }

	// std::cout<<"send msg length "<<sendStr.length() <<"sendstr size "<<sendStr.size()<<std::endl;
	int ret  = send(s,sendStr.c_str(),sendStr.size(),0);
    std::cout<<"client send len="<<ret<<std::endl;
}