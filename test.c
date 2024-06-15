#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "header.h"
#include <signal.h>

void 	ee(int x)
{
	if (x == SIGINT)
	{
	}
}

int main(int argc, char **argv, char **env)
{
	int id = fork();
	if (!id)
	{
		exit(256);
	}
	else
	{
		int st;
		wait(&st);
		printf("\n%d\n", st);
	}
	
}
	

