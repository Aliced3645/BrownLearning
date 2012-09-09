#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAX_LENGTH 256

int main(int argc, char** argv)
{
	int rv;
	int sockd;
	struct addrinfo hints, *servinfo;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if( (rv = getaddrinfo(NULL, "8080", &hints, &servinfo))!= 0){
		printf("%s\n", (char*)strerror(errno));
		exit(0);	
	}
	if((sockd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1){
		close(sockd);
		printf("%s\n", (char*)strerror(errno));
		exit(-1);
	}

	if((rv = bind(sockd, servinfo->ai_addr, servinfo->ai_addrlen)) < 0){
		close(sockd);
		printf("%s\n", (char*)strerror(errno));
		exit(-1);
	}
	printf("server started\n");
	if( (listen(sockd, NULL)) < 0){
		close(sockd);
		printf("%s\n", (char*)strerror(errno));
		exit(-1);
	}
	int client_sockd = accept(sockd, NULL,NULL);
	if(client_sockd == -1){
		close(sockd);
		printf("%s\n", (char*)strerror(errno));
		exit(-1);
	}
	printf("connection established\n");
	char message[MAX_LENGTH];
	memset(message,0, MAX_LENGTH);
	int msglength;
	while( (msglength = recv(client_sockd, message, MAX_LENGTH, 0)) > 0){
		printf("message received: %s\n", message);
		memset(message, 0, MAX_LENGTH);
		fflush(stdout);

	}
	
	
	return (0);
}
