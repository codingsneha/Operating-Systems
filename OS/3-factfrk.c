/*
1. Write a Unix C program using the fork() system call that generates the factorial and
gives a sequence of series like 1, 2, 6, 24, 120… in the child process. The number of the
sequence is provided in the command line. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int factorial(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

int main()
{
    int num_terms = 5; // Set the number of terms to 5

    printf("Factorial Sequence for %d terms:\n", num_terms);

    for (int i = 1; i <= num_terms; i++)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            fprintf(stderr, "Fork Failed.\n");
            return 1;
        }
        else if (pid == 0)
        {
            printf("%d! = %d\n", i, factorial(i));
            exit(0);
        }
        else
        {
            wait(NULL);
        }
    }

    return 0;
}
