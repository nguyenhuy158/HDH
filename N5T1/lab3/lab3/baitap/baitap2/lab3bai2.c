#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int re;
    printf("Call system to execute [ls -a]\n");
    re = system("ls -a");
    if (re != -1)
        printf("System call ls -a is done!\n\n");

    printf("Call system to execute [touch file1.txt]\n");
    re = system("touch file1.txt");
    re = system("ls -l");
    if (re != -1)
        printf("System call touch file1.txt is done!\n\n");

    printf("Call system to execute [mkdir file1]\n");
    re = system("mkdir file1");
    re = system("ls -l");
    if (re != -1)
        printf("System call mkdir file1 is done!\n\n");

    printf("Call system to execute [rm file1.txt]\n");
    re = system("rm file1.txt");
    re = system("ls -l");
    if (re != -1)
        printf("System call rm file1.txt is done!\n\n");

    printf("Call system to execute [rm -r file1]\n");
    re = system("rm -r file1");
    re = system("ls -l");
    if (re != -1)
        printf("System call rm -r file1 is done!\n\n");

    printf("Call system to execute [ps -a]\n");
    re = system("ps -a");
    if (re != -1)
        printf("System call ps -a is done!\n\n");
    return 0;
}