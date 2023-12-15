#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define ReadersCount 5
#define WritersCount 5
sem_t mutex,wrt;
int data =0,readers=0;
void *reader(void *arg)
{
	while(1)
	{
		sem_wait(&mutex);
		readers++;
		if(readers == 1)
		{
			sem_wait(&wrt);
		}
		sem_post(&mutex);
		printf("Reader %d reads data: %d\n",*((int*)arg),data);
		sem_wait(&mutex);
		readers--;
		if(readers == 0)
		{
			sem_post(&wrt);
		}
		sem_post(&mutex);
		sleep(1);
	}
	pthread_exit(NULL);
}
void *writer(void *arg)
{
	while(1)
	{
		sem_wait(&wrt);
		data++;
		printf("Writer %d writer data: %d\n",*((int*)arg),data);
		sem_post(&wrt);
		sleep(2);
	}
	pthread_exit(NULL);
}
int main()
{
	pthread_t reader_threads[ReadersCount],writer_threads[WritersCount];
	int reader_ids[ReadersCount],writer_ids[WritersCount];
	sem_init(&mutex,0,1);
	sem_init(&wrt,0,1);
	for(int i = 0;i<ReadersCount;i++)
	{
		reader_ids[i] = i+1;
		pthread_create(&reader_threads[i],NULL,reader,&reader_ids[i]);
	}
	for(int i = 0;i<WritersCount;i++)
	{
		writer_ids[i] = i+1;
		pthread_create(&writer_threads[i],NULL,writer,&writer_ids[i]);
	}
	for(int i = 0;i<ReadersCount;i++)
	pthread_cancel(reader_threads[i]);
	for(int i = 0;i<WritersCount;i++)
	pthread_cancel(writer_threads[i]);
	sem_destroy(&mutex);
	sem_destroy(&wrt);
	return 0;
}
