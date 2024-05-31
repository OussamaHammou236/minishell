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


int main(int argc, char **argv, char **env)
{
	char *cmd[2];
	cmd[0] = "ls";
	cmd[1] = ">>";
	cmd[2] = "der";
	cmd[3] = NULL;

  
}

//ls -l > out 
// type
// out