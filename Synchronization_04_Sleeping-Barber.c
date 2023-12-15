#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define CHAIRS 5

sem_t mutex, barber, customers;
int waiting = 0;

void *barber_thread(void *arg) {
    while (1) {
        // Wait for a customer to arrive
        sem_wait(&customers);
        // Acquire the mutex to modify the waiting count
        sem_wait(&mutex);
        waiting--;
        // Release the mutex
        sem_post(&mutex);

        // Signal the barber semaphore to indicate that the barber is ready to cut hair
        sem_post(&barber);

        // Barber cuts hair
        printf("Barber is cutting hair.\n");

        // Simulate cutting hair
        sleep(2);
    }
}

void *customer_thread(void *arg) {
    // Acquire the mutex to modify the waiting count
    sem_wait(&mutex);

    if (waiting < CHAIRS) {
        waiting++;
        // Signal the customer semaphore to indicate that a customer has arrived
        sem_post(&customers);
        // Release the mutex
        sem_post(&mutex);

        // Wait for the barber to be ready
        sem_wait(&barber);

        // Barber is ready, get a haircut
        printf("Customer is getting a haircut.\n");
    } else {
        // No available chairs, customer leaves
        // Release the mutex without signaling customers semaphore
        sem_post(&mutex);
        printf("No available chairs. Customer is leaving.\n");
    }
}

int main() {
    pthread_t barber_tid, customer_tid;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&barber, 0, 0);
    sem_init(&customers, 0, 0);

    // Create barber thread
    pthread_create(&barber_tid, NULL, barber_thread, NULL);

    // Create customer threads
    for (int i = 0; i < 10; i++) {
        pthread_create(&customer_tid, NULL, customer_thread, NULL);
        sleep(1); // Simulate customers arriving at different times
    }

    // Wait for threads to finish (this is a simple example; in a real program, you would likely use thread management mechanisms)
    pthread_join(barber_tid, NULL);
    pthread_join(customer_tid, NULL);

    // Destroy semaphores when no longer needed
    sem_destroy(&mutex);
    sem_destroy(&barber);
    sem_destroy(&customers);

    return 0;
}
