#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int i;
    int pid = fork();
    int n = atoi(argv[1]);
    if (pid == 0)
    {
        printf("%d", n);
        while (1)
        {
            if (n != 1)
            {
                printf(", ");
            }
            if (n == 1)
            {
                break;
            }
            if (n % 2)
            {
                n = n * 3 + 1;
                printf("%d", n);
            }
            else
            {
                n = n / 2;
                printf("%d", n);
            }
        }

        printf("\nKet thuc tien trinh con \n");
    }
    else
    {
        wait(NULL);
    }
    return 0;
}