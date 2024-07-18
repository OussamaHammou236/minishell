#include "header.h"

int main()
{
	int id = fork();

	if (!id)
	{
		
		exit(4);
	}
	else
	{
		int st;
		wait(&st);
		printf("%d\n", st);
	}

}