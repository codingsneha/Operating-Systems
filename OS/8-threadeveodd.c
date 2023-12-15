#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int max = 100;
int count = 0;
void *evenNum(void *arg)
{
	while (count<=max)
	{
		if(count%2 == 0)
		printf("%d\t",count++);
	}
	pthread_exit(0);
}
void *oddNum(void *arg)
{
	while (count<=max)
	{
		if(count%2 == 1)
		printf("%d\t",count++);
	}
	pthread_exit(0);
}
int main()
{
	pthread_t t1;
	pthread_t t2;
	pthread_create(&t1,0,&evenNum,NULL);
	pthread_create(&t2,0,&oddNum,NULL);
	pthread_join(t1,0);
	pthread_join(t2,0);
	return;
}
