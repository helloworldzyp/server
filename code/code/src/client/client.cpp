#include"inc.h"

int main(){
    struct sockaddr_in peer;
	int s;
	int rc;
	char buf[ 10 ];

	FullAddress(peer,ADDR,PORT);

	s = socket( AF_INET, SOCK_STREAM, 0 );
	if ( s < 0 )
	{
		perror( "socket call failed" );
		exit( 1 );
	}
	rc = connect( s, ( struct sockaddr * )&peer, sizeof( peer ) );
	if ( rc )
	{
		perror( "connect call failed" );
		exit( 1 );
	}
	rc = send( s, "1234", 4, 0 );
	if ( rc <= 0 )
	{
		perror( "send call failed" );
		exit( 1 );
	}
	rc = recv( s, buf, 1, 0 );
	if ( rc <= 0 )
		perror( "recv call failed" );
	else
		printf( "%c\n", buf[ 0 ] );
    std::cout<<"client"<<std::endl;
}