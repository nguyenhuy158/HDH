#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int i;
    int pid = fork();
    if (pid == 0)
    {
        int re;
        printf("Call system to execute %s\n", argv[1]);
        re = system(argv[1]);
        if (re != -1)
            printf("System call done!\n\n");
    }
    else
    {
        wait(NULL);
    }
    return 0;
}