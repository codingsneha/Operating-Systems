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

    // Process 2 writes '2' and 'hello' to shared memory
    strcpy(shm, "2");
    printf("Process 2 wrote '2' to shared memory\n");

    // Wait for Process 3 to write data
    printf("Process 2 waiting for Process 3...\n");
    while (strcmp(shm, "2") == 0) {
        sleep(1);
    }

    // Print data written by Process 3
    printf("Process 2 read from shared memory: %s\n", shm);

    // Detach the shared memory segment
    shmdt(shm);

    return 0;
}
