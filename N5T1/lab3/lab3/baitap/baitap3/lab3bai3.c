#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{

    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        printf("fork error !No child created\n");
    }
    else if (pid == 0)
    {
        printf("My ID B: %d and my Parent: %d\n", getpid(), getppid());
        pid = fork();
        if (pid < 0)
        {
            printf("fork error !No child created\n");
        }
        else if (pid == 0)
        {
            printf("My ID D: %d and my Parent: %d\n", getpid(), getppid());
            sleep(1);
            exit(0);
        }
        pid = fork();
        if (pid < 0)
        {
            printf("fork error !No child created\n");
        }
        else if (pid == 0)
        {
            printf("My ID E: %d and my Parent: %d\n", getpid(), getppid());
            sleep(1);
            exit(0);
        }
        sleep(1);
        exit(0);
    }

    pid = fork();
    if (pid < 0)
    {
        printf("fork error !No child created\n");
    }
    else if (pid == 0)
    {
        printf("My ID C: %d and my Parent: %d\n", getpid(), getppid());
        pid = fork();
        if (pid < 0)
        {
            printf("fork error !No child created\n");
        }
        else if (pid == 0)
        {
            printf("My ID H: %d and my Parent: %d\n", getpid(), getppid());
            sleep(1);
            exit(0);
        }
        sleep(1);
        exit(0);
    }

    printf("My ID A: %d and my Parent: %d\n", getpid(), getppid());
    return 0;
}