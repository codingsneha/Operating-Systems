#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

pthread_t tidp[10], tidc[10];
pthread_mutex_t mutex;
sem_t full;
sem_t empty;
int buffer[10];
int counter;

// Function prototypes
void initialize();
void *producer(void *prod);
void *consumer(void *cons);
void produce(int x);
int consume();

int main()
{
    initialize();
    int n1, n2, i;
    printf("Enter no. of producer processes: ");
    scanf("%d", &n1);
    printf("Enter the number of consumer processes: ");
    scanf("%d", &n2);
    for (i = 0; i < n1; i++)
    {
        pthread_create(&tidp[i], NULL, producer, NULL);
    }
    for (i = 0; i < n2; i++)
    {
        pthread_create(&tidc[i], NULL, consumer, NULL);
    }
    for (i = 0; i < n1; i++)
    {
        pthread_join(tidp[i], NULL);
    }
    for (i = 0; i < n2; i++)
    {
        pthread_join(tidc[i], NULL);
    }

    return 0;
}

void initialize()
{
    counter = 0;
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 10);
    pthread_mutex_init(&mutex, NULL);
}

void *producer(void *prod)
{
    int item;
    item = rand() % 10;
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    produce(item);
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

void *consumer(void *cons)
{
    int item;
    do
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = consume();
        if (item != -1)
        {
            printf("Consumer consumed: %d\n", item);
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(1);
    } while (1);
}


void produce(int x)
{
    if (counter >= 9)
    {
        printf("No more space left\n");
    }
    else
    {
        buffer[counter++] = x;
        printf("Producer Added: %d\n", x);
    }
}

int consume()
{
    if (counter <= 0)
    {
        printf("No item\n");
        return -1;
    }
    else
    {
        return buffer[--counter];
    }
}
