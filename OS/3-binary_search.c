/*
Implement the C program in which main program accepts an integer array. Main
program uses the fork system call to create a new process called a child process. Parent
process sorts an integer array and passes the sorted array to child process through the
command line arguments of execve system call. The child process uses execve system
call to load new program that uses this sorted array for performing the binary search
to search the particular item in the array.
*/

#include<stdio.h>
#include"binary.h"
void main()
{
	int arr[20],i,total;
	printf("Enter the no of elements:");
	scanf("%d",&total);
	printf("Entet the elements:");
	for(i=0;i<total;i++)
	{
		scanf("%d",&arr[i]);
	}
	binary_search(arr,total);
}

