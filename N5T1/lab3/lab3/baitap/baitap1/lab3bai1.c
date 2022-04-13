#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    pid_t pid;

    pid = fork();
    int n = atoi(argv[1]);
    if (pid < 0)
    {
        printf("fork error !No child created\n");
    }
    else if (pid == 0)
    {
        int tongUoc = 0;
        for (int i = 1; i <= n; i++)
        {
            if (n % i == 0)
            {
                tongUoc += i;
            }
        }
        printf("Tong uoc cua %d la %d\n", n, tongUoc);
    }
    else
    {
        int tong = 0;
        for (int i = 1; i <= n; i++)
        {
            tong += i;
        }
        printf("Tong tu 1 -> %d la %d\n", n, tong);
    }
    return 0;
}