#include "stdio.h"
#include <pthread.h>
#include <semaphore.h>

//some changes
typedef unsigned int semaphore;

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


semaphore P(semaphore s){
	if ( s > 0 )
		s --;
	else
		while(!s);
}

semaphore V(semaphore s){
	s ++;
	return s;
}

//Producer Consumer Problem
semaphore empty = 10;
semaphore occupied = 0;
int nextin = 0;
int nextout = 0;
char buffer[10];

void Producer(char item){
	
	P(empty);
	buffer[nextin] = item;
	nextin ++;
	if(nextin == 10)
		nextin = 0;
	V(occupied);

}

char Consumer(){
	
	P(occupied);
	char item;
	item = buffer[nextout];
	nextout ++;
	if(nextout == 10)
		nextout = 0;
	V(empty);
	return item;	
}

int main()
{
	start_servers();
	//while(1);

	//mutex
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	int x;
	pthread_mutex_lock(&m);
	x = x + 1;
	pthread_mutex_unlock(&m);

	//semaphore
	sem_t semaphore;
	int err;
	err = sem_init(&semaphore, 0, 10);
	err = sem_wait(&semaphore);
	err = sem_post(&semaphore);

	return 0;
}



