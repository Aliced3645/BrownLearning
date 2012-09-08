#include "stdio.h"
#include <pthread.h>
//some changes

typedef struct{
	int first,second;
}two_ints_t;

void* server(void *arg){
	int i = 0;
	int r = 15;
	while(1){
		printf("%d\n",i);
		i ++;
		if(i == 10)
		{
			pthread_exit((void*)&r);
		}
	}

}

pthread_t start_servers(){
	pthread_t thread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr,20*1024*1024);
	int i;
	void **r = 0;
	for(i = 0; i < 5; i ++)
	{
		pthread_create(&thread,&attr,server,0);
		pthread_join(thread,r);	
		//printf("%d\n", (int)(*((int**)r)[1]));
	}
	return thread;

}

int main()
{
	start_servers();
	//while(1);
	return 0;
}

