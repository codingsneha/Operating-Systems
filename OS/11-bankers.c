#include <stdio.h>

#define NUMBER_OF_PROCESSES 5
#define NUMBER_OF_RESOURCES 3

// Available resources
int available[NUMBER_OF_RESOURCES] = {3, 3, 2};

// Maximum resources that can be allocated to processes
int maximum[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

// Allocated resources to processes
int allocation[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

// Need of resources for each process
int need[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES];

// Mark processes as finished or not
int finish[NUMBER_OF_PROCESSES];

// Initialize the need matrix and finish array
void initialize() {
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        finish[i] = 0;
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

// Find the safe sequence
void findSafeSequence() {
    int work[NUMBER_OF_RESOURCES];
    int safeSequence[NUMBER_OF_PROCESSES];
    int count = 0;

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        work[i] = available[i];
    }

    while (count < NUMBER_OF_PROCESSES) {
        int found = 0;
        for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == NUMBER_OF_RESOURCES) {
                    for (int k = 0; k < NUMBER_OF_RESOURCES; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("System is not in safe state.\n");
            return;
        }
    }

    printf("System is in safe state.\nSafe sequence is: ");
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        printf("P%d ", safeSequence[i]);
    }
}

// Print the resource allocation table
void printTable() {
    printf("Process\tAllocation\tMax\t\tNeed\n");
    for (int i = 0; i < NUMBER_OF_PROCESSES; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("%d ", maximum[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

int main() {
    initialize();
    printTable();
    findSafeSequence();
    return 0;
}
