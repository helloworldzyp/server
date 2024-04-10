#include"inc.h"
#define INVAILD_NUM  -1

int main(){
    struct sockaddr_in local;
	int s;
	int s1;
	int rc;
	char buf[ 10 ];

	FullAddress(local,ADDR,PORT);
	s = socket( AF_INET, SOCK_STREAM, 0 );
	if ( s < 0 )
	{
		perror( "socket call failed" );
		exit( 1 );
	}

    int on = 1;
    setsockopt( s, SOL_SOCKET, SO_REUSEADDR, &on,sizeof( on ));
    std::cout<<"new_1"<<std::endl;
	rc = bind( s, ( struct sockaddr * )&local, sizeof( local ) );
	if ( rc < 0 )
	{
		perror( "bind call failure" );
		exit( 1 );
	}
	rc = listen( s, 5 );
	if ( rc )
	{
		perror( "listen call failed" );
		exit( 1 );
	}
	s1 = accept( s, NULL, NULL );
	if ( s1 < 0 )
	{
		perror( "accept call failed" );
		exit( 1 );
	}
	rc = readn( s1, buf, 2);
	if ( rc <= 0 )
	{
		perror( "recv call failed" );
		exit( 1 );
	}
    buf[rc] = '\0';
	std::cout<<buf<<std::endl;
	rc = send( s1, "2", 1, 0 );
	if ( rc <= 0 )
		perror( "send call failed" );
    std::cout<<"server1 "<<std::endl;
}