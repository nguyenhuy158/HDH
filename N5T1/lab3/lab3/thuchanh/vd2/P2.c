// P2.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    fork();
    printf("Hello world! from Process ID: %d\n", getpid());
    return 0;
}