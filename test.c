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

void signalll(int x)
{
  
}

int main(int argc, char **argv, char **env)
{
	int pid = fork();
    int s;
    signal(SIGQUIT, signalll);
    if (!pid)
    {
        
        char *cmd[2];
        cmd[0] = "cat";
        cmd[1] = NULL;
        execve("/usr/bin/cat", cmd, env);
    }
    else
    {
        wait(&s);
    }
}
	

