/*
enging.
Four threads are involved: an agent and three smokers. The smokers loop
forever, first waiting for ingredients, then making and smoking cigarettes. The
ingredients are tobacco, paper, and matches.
We assume that the agent has an infinite supply of all three ingredients, and
each smoker has an infinite supply of one of the ingredients; that is, one smoker
has matches, another has paper, and the third has tobacco.
The agent repeatedly chooses two different ingredients at random and makes
them available to the smokers. Depending on which ingredients are chosen, the
smoker with the complementary ingredient should pick up both resources and
proceed.
For example, if the agent puts out tobacco and paper, the smoker with the
matches should pick up both ingredients, make a cigarette, and then signal the
agent.

Smoker problem solution
Here is the code for one of the pushers:
Pusher A
1 tobacco . wait ()
2 mutex . wait ()
3 if isPaper :
4 isPaper = False
5 matchSem . signal ()
6 elif isMatch :
7 isMatch = False
8 paperSem . signal ()
9 else :
10 isTobacco = True
11 mutex . signal ()
This pusher wakes up any time there is tobacco on the table. If it finds
isPaper true, it knows that Pusher B has already run, so it can signal the
smoker with matches. Similarly, if it finds a match on the table, it can signal
the smoker with paper.
But if Pusher A runs first, then it will find both isPaper and isMatch false.
It cannot signal any of the smokers, so it sets isTobacco.
The other pushers are similar. Since the pushers do all the real work, the
smoker code is trivial:
Smoker with tobacco
1 tobaccoSem . wait ()
2 makeCigarette ()
3 agentSem . signal ()
4 smoke ()


*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

// Semaphores
sem_t agentSem, tobaccoSem, paperSem, matchSem;
sem_t mutex;

// Flags to indicate the availability of ingredients
int isTobacco = 0, isPaper = 0, isMatch = 0;

// Function prototypes
void *agent(void *arg);
void *pusherA(void *arg);
void *pusherB(void *arg);
void *pusherC(void *arg);
void *smokerTobacco(void *arg);
void *smokerPaper(void *arg);
void *smokerMatch(void *arg);

int main() {
    // Initialize semaphores
    sem_init(&agentSem, 0, 1);
    sem_init(&tobaccoSem, 0, 0);
    sem_init(&paperSem, 0, 0);
    sem_init(&matchSem, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create threads for the agent, pushers, and smokers
    pthread_t agentThread, pusherAThread, pusherBThread, pusherCThread, smokerTobaccoThread, smokerPaperThread, smokerMatchThread;

    pthread_create(&agentThread, NULL, agent, NULL);
    pthread_create(&pusherAThread, NULL, pusherA, NULL);
    pthread_create(&pusherBThread, NULL, pusherB, NULL);
    pthread_create(&pusherCThread, NULL, pusherC, NULL);
    pthread_create(&smokerTobaccoThread, NULL, smokerTobacco, NULL);
    pthread_create(&smokerPaperThread, NULL, smokerPaper, NULL);
    pthread_create(&smokerMatchThread, NULL, smokerMatch, NULL);

    // Wait for threads to finish (this is a simple example; in a real program, you would likely use thread management mechanisms)
    pthread_join(agentThread, NULL);
    pthread_join(pusherAThread, NULL);
    pthread_join(pusherBThread, NULL);
    pthread_join(pusherCThread, NULL);
    pthread_join(smokerTobaccoThread, NULL);
    pthread_join(smokerPaperThread, NULL);
    pthread_join(smokerMatchThread, NULL);

    // Destroy semaphores when no longer needed
    sem_destroy(&agentSem);
    sem_destroy(&tobaccoSem);
    sem_destroy(&paperSem);
    sem_destroy(&matchSem);
    sem_destroy(&mutex);

    return 0;
}

void *agent(void *arg) {
    while (1) {
        sem_wait(&agentSem);

        // Choose two random ingredients
        int randIngredients = rand() % 3;

        switch (randIngredients) {
            case 0:
                sem_post(&tobaccoSem);
                sem_post(&paperSem);
                break;
            case 1:
                sem_post(&paperSem);
                sem_post(&matchSem);
                break;
            case 2:
                sem_post(&tobaccoSem);
                sem_post(&matchSem);
                break;
        }
    }
}

void *pusherA(void *arg) {
    while (1) {
        sem_wait(&tobaccoSem);
        sem_wait(&mutex);

        if (isPaper) {
            isPaper = 0;
            sem_post(&matchSem);
        } else if (isMatch) {
            isMatch = 0;
            sem_post(&paperSem);
        } else {
            isTobacco = 1;
        }

        sem_post(&mutex);
    }
}

void *pusherB(void *arg) {
    while (1) {
        sem_wait(&paperSem);
        sem_wait(&mutex);

        if (isTobacco) {
            isTobacco = 0;
            sem_post(&matchSem);
        } else if (isMatch) {
            isMatch = 0;
            sem_post(&tobaccoSem);
        } else {
            isPaper = 1;
        }

        sem_post(&mutex);
    }
}

void *pusherC(void *arg) {
    while (1) {
        sem_wait(&matchSem);
        sem_wait(&mutex);

        if (isTobacco) {
            isTobacco = 0;
            sem_post(&paperSem);
        } else if (isPaper) {
            isPaper = 0;
            sem_post(&tobaccoSem);
        } else {
            isMatch = 1;
        }

        sem_post(&mutex);
    }
}

void *smokerTobacco(void *arg) {
    while (1) {
        sem_wait(&tobaccoSem);
        printf("Smoker with tobacco is making and smoking a cigarette.\n");
        sleep(2);
        sem_post(&agentSem); // Signal agent to provide new ingredients
    }
}

void *smokerPaper(void *arg) {
    while (1) {
        sem_wait(&paperSem);
        printf("Smoker with paper is making and smoking a cigarette.\n");
        sleep(2);
        sem_post(&agentSem); // Signal agent to provide new ingredients
    }
}

void *smokerMatch(void *arg) {
    while (1) {
        sem_wait(&matchSem);
        printf("Smoker with matches is making and smoking a cigarette.\n");
        sleep(2);
        sem_post(&agentSem); // Signal agent to provide new ingredients
    }
}
