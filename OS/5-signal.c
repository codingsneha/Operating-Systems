/*
Implement the C program to demonstrate the use of SIGCHLD signal. A parent
process Creates multiple child process (minimum three child processes). Parent
process should be Sleeping until it creates the number of child processes. Child
processes send SIGCHLD signal to parent process to interrupt from the sleep and
force the parent to call wait for the Collection of status of terminated child processes. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

// Number of child processes to create
#define NUM_CHILDREN 3

// Signal handler for SIGCHLD
void sigchld_handler(int signo) {
    int status;
    pid_t child_pid;

    // Collect status of terminated child processes
    while ((child_pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Child process %d terminated with status %d\n", child_pid, WEXITSTATUS(status));
    }
}

int main() {
    pid_t child_pid;
    int i;

    // Register SIGCHLD signal handler
    signal(SIGCHLD, sigchld_handler);

    // Create child processes
    for (i = 0; i < NUM_CHILDREN; ++i) {
        child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Child process
            printf("Child process %d created\n", getpid());
            sleep(2);  // Simulate some work in child process
            exit(0);
        }
    }

    // Parent process
    printf("Parent process sleeping...\n");
    sleep(10);  // Parent sleeps, waiting for signals

    printf("Parent process woke up\n");

    // Parent can continue with other tasks after handling SIGCHLD
    while (1) {
        // Do some work in the parent process
        sleep(1);
    }

    return 0;
}


/*
The parent process creates multiple child processes using a loop and fork.
The child processes simulate some work using sleep(2) and then exit.
The parent process sleeps for 10 seconds to allow child processes to terminate.
The parent process registers a signal handler for SIGCHLD using signal(SIGCHLD, sigchld_handler).
When a child process terminates, it sends the SIGCHLD signal to the parent process.
The sigchld_handler function is called when SIGCHLD is received, and it uses waitpid to collect the status of terminated child processes.
Compile and run this program to observe the behavior. You should see output messages indicating the creation and termination of child processes.
*/