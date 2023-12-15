/*
Write a C program to implement the following game. The parent program P first
creates two pipes, and then spawns two child processes C and D. One of the two pipes
is meant for communications between P and C, and the other for communications
between P and D. Now, a loop runs as follows. In each iteration (also called round), P
first randomly chooses one of the two flags: MIN and MAX (the choice randomly
varies from one iteration to another). Each of the two child processes C and D
generates a random positive integer and sends that to P via its pipe. P reads the two
integers; let these be c and d. If P has chosen MIN, then the child who sent the smaller
of c and d gets one point. If P has chosen MAX, then the sender of the larger of c and
d gets one point. If c = d, then this round is ignored. The child process who first obtains
ten points wins the game. When the game ends, P sends a user-defined signal to both
C and D, and the child processes exit after handling the signal (in order to know who
was the winner). After C and D exit, the parent process P exits. During each iteration
of the game, P should print appropriate messages (like P's choice of the flag, the
integers received from C and D, which child gets the point, the current scores of C
and D) in order to let the user know how the game is going on. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define ROUNDS 50
#define TARGET_SCORE 10

int main() {
    int pipe1[2], pipe2[2];
    pid_t childC, childD;
    int scoreC = 0, scoreD = 0;

    // Create two pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create child process C
    if ((childC = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (childC == 0) {  // Child C process
        close(pipe1[0]); // Close reading end
        srand(getpid());
        while (1) {
            int number = rand() % 100 + 1; // Generate a random positive integer
            write(pipe1[1], &number, sizeof(number));
            sleep(1); // Give parent some time to read
        }
    }

    // Create child process D
    if ((childD = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (childD == 0) {  // Child D process
        close(pipe2[0]); // Close reading end
        srand(getpid());
        while (1) {
            int number = rand() % 100 + 1; // Generate a random positive integer
            write(pipe2[1], &number, sizeof(number));
            sleep(1); // Give parent some time to read
        }
    }

    // Parent process
    close(pipe1[1]); // Close writing end of pipe1
    close(pipe2[1]); // Close writing end of pipe2

    srand(getpid());

    for (int round = 1; round <= ROUNDS; ++round) {
        int choice = rand() % 2; // Randomly choose MIN (0) or MAX (1)
        int numberC, numberD;

        if (choice == 0) {
            // P chooses MIN
            read(pipe1[0], &numberC, sizeof(numberC));
            read(pipe2[0], &numberD, sizeof(numberD));
            if (numberC < numberD) {
                scoreC++;
                printf("Round %d: P chooses MIN. C:%d, D:%d. C gets a point.\n", round, numberC, numberD);
            } else if (numberC > numberD) {
                scoreD++;
                printf("Round %d: P chooses MIN. C:%d, D:%d. D gets a point.\n", round, numberC, numberD);
            } else {
                printf("Round %d: P chooses MIN. C:%d, D:%d. It's a tie.\n", round, numberC, numberD);
            }
        } else {
            // P chooses MAX
            read(pipe1[0], &numberC, sizeof(numberC));
            read(pipe2[0], &numberD, sizeof(numberD));
            if (numberC > numberD) {
                scoreC++;
                printf("Round %d: P chooses MAX. C:%d, D:%d. C gets a point.\n", round, numberC, numberD);
            } else if (numberC < numberD) {
                scoreD++;
                printf("Round %d: P chooses MAX. C:%d, D:%d. D gets a point.\n", round, numberC, numberD);
            } else {
                printf("Round %d: P chooses MAX. C:%d, D:%d. It's a tie.\n", round, numberC, numberD);
            }
        }

        printf("Current Scores: C:%d, D:%d\n", scoreC, scoreD);

        if (scoreC == TARGET_SCORE || scoreD == TARGET_SCORE) {
            printf("Game Over! Winner is %s\n", (scoreC == TARGET_SCORE) ? "C" : "D");

            // Send a user-defined signal to both child processes
            kill(childC, SIGUSR1);
            kill(childD, SIGUSR1);

            // Wait for child processes to exit
            waitpid(childC, NULL, 0);
            waitpid(childD, NULL, 0);

            // Close reading end of pipes
            close(pipe1[0]);
            close(pipe2[0]);

            exit(EXIT_SUCCESS);
        }
    }

    // Close reading end of pipes
    close(pipe1[0]);
    close(pipe2[0]);

    // Wait for child processes to exit
    waitpid(childC, NULL, 0);
    waitpid(childD, NULL, 0);

    return 0;
}
