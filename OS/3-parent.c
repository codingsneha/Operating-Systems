
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <element_to_search> <element1> <element2> ... <elementN>\n", argv[0]);
        return 1;
    }

    int elementToSearch = atoi(argv[1]);
    int n = argc - 2;
    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 2]);
    }

    // Sort the array
    bubbleSort(arr, n);

    // Create a child process
    pid_t child_pid = fork();

    if (child_pid == 0) {
        // Child process
        execv("./child", argv);
    } else if (child_pid > 0) {
        // Parent process
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
    } else {
        perror("fork");
        return 1;
    }

    free(arr);
    return 0;
}