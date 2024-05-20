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
    int fd[2];
    pipe(fd);

    int i = 0;

    while (i < 2)
    {
        int id = fork();

        if (!id)
        {
            if (i == 0)
            {
                close(fd[0]);
                dup2(fd[1], 1);
                printf("whatever");
                close(fd[1]);
            }
            else
            {
                close(fd[1]);
                char buff[200];
                read(fd[0], buff, 200);
                printf("%s12\n", buff);
                close(fd[0]);
            }
            exit(0);
        }
        else
        {
            int st;
            wait(&st);
            if (i == 2)
            {
                close(fd[1]);
                close(fd[0]);
            }
        }
        i++;
    }

  
}

