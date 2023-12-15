#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_SIZE 100

int main() {
    key_t key = ftok(".", 'a');
    int shmid;
    char *shm;

    // Create a shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Process 1 writes '1' to the shared memory
    strcpy(shm, "1");
    printf("Process 1 wrote '1' to shared memory\n");

    // Wait for Process 2 to write data
    printf("Process 1 waiting for Process 2...\n");
    while (strcmp(shm, "1") == 0) {
        sleep(1);
    }

    // Print data written by Process 2
    printf("Process 1 read from shared memory: %s\n", shm);

    // Detach the shared memory segment
    shmdt(shm);

    // Wait for child processes to complete
    wait(NULL);

    // Remove the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
