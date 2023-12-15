#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>  // Include for the sleep function
#define bs 4

sem_t mutex, empty, full;
int buffer[bs];
int i = 1, c = 0;

//Producer process
void producer() {
    while (1) {
        printf("\nItem%d produced.", i);
        int item = i++;
        // Wait for an empty slot in buffer
        sem_wait(&empty);
        // Enter critical section
        sem_wait(&mutex);
        // Add item to buffer
        buffer[c++] = item;
        // Exit critical section
        sem_post(&mutex);
        // Signal that a slot is filled in buffer
        sem_post(&full);
        // Introduce a sleep to slow down the output
        sleep(1);
    }
}

//Consumer Process
void consumer() {
    while (1) {
        // Wait for a filled slot
        sem_wait(&full);
        // Enter critical section
        sem_wait(&mutex);
        // Remove an item from buffer
        int consumedItem = buffer[c--];
        // Exit critical section
        sem_post(&mutex);
        // Signal that an empty slot is available in buffer
        sem_post(&empty);
        // Consume the item
        printf("\nItem%d consumed.", consumedItem+1);
        // Introduce a sleep to slow down the output
        sleep(2);
    }
}

int main() {
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, bs);
    sem_init(&full, 0, 0);

    // Create threads for producer and consumer
    pthread_t producerThread, consumerThread;

    if (pthread_create(&producerThread, NULL, (void *)producer, NULL) != 0) {
        perror("Error creating producer thread");
        return 1;
    }

    if (pthread_create(&consumerThread, NULL, (void *)consumer, NULL) != 0) {
        perror("Error creating consumer thread");
        return 1;
    }

    // Wait for threads to finish (this is a simple example; in a real program, you would likely use thread management mechanisms)
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy semaphores when no longer needed
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}
