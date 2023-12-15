/*  imagine that threads represent ballroom dancers and that two
kinds of dancers, leaders and followers, wait in two queues before entering the
dance floor. When a leader arrives, it checks to see if there is a follower waiting.
If so, they can both proceed. Otherwise it waits.
Similarly, when a follower arrives, it checks for a leader and either proceeds
or waits, accordingly.
 */

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t leaderQueue, followerQueue;

void *leaders() {
    while(1) {
        sem_post(&followerQueue);
        sem_wait(&leaderQueue);
        printf(" Leader ");
        sleep(2);
    }
}

void *followers() {
    while(1) {
        sem_post(&leaderQueue);
        sem_wait(&followerQueue);
        printf(" Follower ");
        sleep(1);
    }
}

int main() {
    sem_init(&leaderQueue, 0, 0);
    sem_init(&followerQueue, 0, 0);

    pthread_t leader, follower;

    pthread_create(&leader, NULL, &leaders, NULL);
    pthread_create(&follower, NULL, &followers, NULL);

    pthread_join(leader, NULL);
    pthread_join(follower, NULL);
    
    

    sem_destroy(&leaderQueue);
    sem_destroy(&followerQueue);
    return 0;
}