#include "stdio.h"
#include <pthread.h>
//some changes

typedef struct{
	int first,second;
}two_ints_t;

void* server(void *arg){
	int i = 0;
	while(1){
		printf("%d\n",i);
		i ++;
		if(i == 10)
		{
			pthread_exit(0);
		}
	}

}

pthread_t start_servers(){
	pthread_t thread;
	int i;
	for(i = 0; i < 5; i ++)
	{
		pthread_create(&thread,0,server,0);
		pthread_join(thread,0);	
	}
	return thread;

}

int main()
{
	start_servers();
	//while(1);
	return 0;
}

