#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void forkexample()
{
	int x = 1;
	pid_t p = fork();
	if (p<0)
	{
		perror("Fork fail");
		exit(1);
	}
	else if(p==0)
	{
		printf("Child has p = %d\n",p);
	}
	else
	{
		printf("Parent has p = %d\n",p);
	}
}
int main()
{
	forkexample();
	return 0;
}
