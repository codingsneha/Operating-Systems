/*

there is no guarantee that customers are served in the
order they arrive. Up to n customers can pass the turnstile, signal customer
and wait on barber. When the barber signal barber, any of the customers
might proceed.
Modify this solution so that customers are served in the order they pass the
turnstile.

FIFO barbershop solution (customer)
1 self . sem = Semaphore (0)
2 mutex . wait ()
3 if customers == n :
4 mutex . signal ()
5 balk ()
6 customers += 1
7 queue . append ( self . sem )
8 mutex . signal ()
9
10 customer . signal ()
11 self . sem . wait ()
12
13 # getHairCut ()
14
15 customerDone . signal ()
16 barberDone . wait ()
17
18 mutex . wait ()
19 customers -= 1
20 mutex . signal ()

FIFO barbershop solution (barber)
1 customer . wait ()
2 mutex . wait ()
3 sem = queue . pop (0)
4 mutex . signal ()
5
6 sem . signal ()
7
8 # cutHair ()
9
10 customerDone . wait ()
11 barberDone . signal ()
*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define N 5 // Number of customers

sem_t mutex, customer, barber, customerDone, barberDone;
int customers = 0;

void balk() {
    printf("Customer balks.\n");
}

void getHairCut() {
    printf("Customer is getting a haircut.\n");
    sleep(1);
}

void cutHair() {
    printf("Barber is cutting hair.\n");
    sleep(2);
}

void *customerThread(void *arg) {
    sem_t *customerSem = (sem_t *)arg;

    sem_wait(&mutex);

    if (customers == N) {
        sem_post(&mutex);
        balk();
    } else {
        customers++;
        sem_post(&mutex);

        sem_post(&customer);
        sem_wait(customerSem);

        getHairCut();

        sem_post(&customerDone);
        sem_wait(&barberDone);

        sem_wait(&mutex);
        customers--;
        sem_post(&mutex);
    }

    pthread_exit(NULL);
}

void *barberThread(void *arg) {
    while (1) {
        sem_wait(&customer);
        sem_wait(&mutex);

        sem_t *customerSem;
        sem_getvalue(&customer, (int *)&customerSem);

        sem_post(&mutex);

        sem_wait(customerSem);

        cutHair();

        sem_post(&barberDone);
        sem_wait(&customerDone);
    }
}

int main() {
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&customer, 0, 0);
    sem_init(&barber, 0, 0);
    sem_init(&customerDone, 0, 0);
    sem_init(&barberDone, 0, 0);

    // Create threads for the barber and customers
    pthread_t barberThreadID;
    pthread_t customerThreadIDs[N];

    pthread_create(&barberThreadID, NULL, barberThread, NULL);

    for (int i = 0; i < N; i++) {
        sem_t *customerSem = (sem_t *)malloc(sizeof(sem_t));
        sem_init(customerSem, 0, 0);

        pthread_create(&customerThreadIDs[i], NULL, customerThread, (void *)customerSem);
    }

    // Wait for threads to finish (this is a simple example; in a real program, you would likely use thread management mechanisms)
    pthread_join(barberThreadID, NULL);

    for (int i = 0; i < N; i++) {
        pthread_join(customerThreadIDs[i], NULL);
    }

    // Destroy semaphores when no longer needed
    sem_destroy(&mutex);
    sem_destroy(&customer);
    sem_destroy(&barber);
    sem_destroy(&customerDone);
    sem_destroy(&barberDone);

    return 0;
}
