// main.c

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    if (argc > 2)
    {
        printf("Co qua nhieu doi so");
    }
    else if (n <= 0)
    {
        printf("Doi so khong phai la so nguyen duong");
    }
    else
    {
        printf("Cac uoc so cua %d la ", n);
        for (int i = 1; i <= n; i++)
        {
            if (n % i == 0)
            {
                printf("%d, ", i);
            }
        }

        int prime = 2;
        int count = 0;
        printf("\n%d = ", n);
        while (1)
        {
            if (n % prime == 0)
            {
                n /= prime;
                count++;
                continue;
            }
            else if (n == 1)
            {
                if (count == 1)
                {
                    printf("%d", prime);
                }
                else
                {
                    printf("%d^%d", prime, count);
                }
                break;
            }
            else
            {
                if (count == 1)
                {
                    printf("%d*", prime);
                }
                else if (count > 1)
                {
                    printf("%d^%d*", prime, count);
                }
            }
            count = 0;
            prime++;
        }
    }
    printf("\n");
    return 0;
}