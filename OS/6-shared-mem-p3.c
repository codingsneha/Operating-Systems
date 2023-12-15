#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 100

int main() {
    key_t key = ftok(".", 'a');
    int shmid;
    char *shm;

    // Attach the shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, 0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Process 3 writes '3' and 'memory' to shared memory
    strcpy(shm, "3");
    printf("Process 3 wrote '3' to shared memory\n");

    // Detach the shared memory segment
    shmdt(shm);

    return 0;
}
