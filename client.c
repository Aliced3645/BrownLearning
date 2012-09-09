#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#define MAX_LENGTH 256
int main(int argc, char** argv)
{
	int sockd;
	struct addrinfo hints, *servinfo;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	int rv = 0;
	if((rv = getaddrinfo("localhost","8080",&hints, &servinfo) != 0)){
		printf("%s\n", strerror(errno));
		exit(-1);
	}
	if((sockd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1){
		printf("%s\n", strerror(errno));
		exit(-1);
	}
	if((rv = connect(sockd,servinfo->ai_addr,servinfo->ai_addrlen)) == -1){
		printf("%s\n",strerror(errno));
		//If "connection refused, that is there is no server started yet
		exit(-1);
	}
	char message[MAX_LENGTH];
	memset(message,0,MAX_LENGTH);
	while(1){
		scanf("%s", message);
		if(strcmp(message,"exit") == 0)
			break;
		else{
			send(sockd, (void*)message, strlen(message), 0);		
		}
		memset(message,0, MAX_LENGTH);
		fflush(stdout);
	}
	

	return (0);
}
