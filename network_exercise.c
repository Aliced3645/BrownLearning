
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

//#define NULL 0
int main(int argc, char** argv){
//	int res = getaddrinfo("localhost","5050",NULL,NULL);
	int fd;
	struct addrinfo hints, *servinfo;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	getaddrinfo("127.0.0.1","5555", &hints, &servinfo);
	fd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	printf("%d\n", fd);
	
	return (0);
}


