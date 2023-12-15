/*
A tribe of savages eats communal dinners from a large pot that
can hold M servings of stewed missionary1
. When a savage wants to
eat, he helps himself from the pot, unless it is empty. If the pot is
empty, the savage wakes up the cook and then waits until the cook
has refilled the pot.
Any number of savage threads run the following code:
Unsynchronized savage code
1 while True :
2 getServingFromPot ()
3 eat ()
And one cook thread runs this code:
Unsynchronized cook code
1 while True :
2 putServingsInPot ( M)

The synchronization constraints are:
• Savages cannot invoke getServingFromPot if the pot is empty.
• The cook can invoke putServingsInPot only if the pot is empty.

Solution
Dining Savages solution (cook)
1 while True :
2 emptyPot . wait ()
3 putServingsInPot ( M)
4 fullPot . signal ()

Dining Savages solution (savage)
1 while True :
2 mutex . wait ()
3 if servings == 0:
4 emptyPot . signal ()
5 fullPot . wait ()
6 servings = M
7 servings -= 1
8 getServingFromPot ()
9 mutex . signal ()
10
11 eat ()

*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define M 5 // Maximum servings in the pot

sem_t mutex, emptyPot, fullPot;
int servings = 0;

void *cook(void *arg) {
    while (1) {
        sem_wait(&emptyPot); // Wait for the pot to be empty
        printf("Cook is refilling the pot.\n");
        servings = M;
        sem_post(&fullPot); // Signal that the pot is full
    }
}

void *savage(void *arg) {
    while (1) {
        sem_wait(&mutex); // Enter critical section

        if (servings == 0) {
            sem_post(&emptyPot); // Signal the cook that the pot is empty
            sem_wait(&fullPot); // Wait for the pot to be refilled
        }

        servings--;
        printf("Savage is getting a serving. Servings left: %d\n", servings);

        sem_post(&mutex); // Exit critical section

        // Simulate eating
        sleep(1);
    }
}

int main() {
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&emptyPot, 0, 0);
    sem_init(&fullPot, 0, 0);

    // Create threads for the cook and savages
    pthread_t cookThread;
    pthread_t savageThreads[M];

    pthread_create(&cookThread, NULL, cook, NULL);

    for (int i = 0; i < M; i++) {
        pthread_create(&savageThreads[i], NULL, savage, NULL);
    }

    // Wait for threads to finish (this is a simple example; in a real program, you would likely use thread management mechanisms)
    pthread_join(cookThread, NULL);

    for (int i = 0; i < M; i++) {
        pthread_join(savageThreads[i], NULL);
    }

    // Destroy semaphores when no longer needed
    sem_destroy(&mutex);
    sem_destroy(&emptyPot);
    sem_destroy(&fullPot);

    return 0;
}
