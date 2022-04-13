// main.c

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        printf("Co qua nhieu doi so");
    }
    else if (atoi(argv[1]) <= 0)
    {
        printf("Doi so khong phai la so nguyen duong");
    }
    else
    {
        int sum = 0;
        for (int i = 0; i < atoi(argv[1]); i++)
        {
            sum += (i + 1);
        }
        printf("s = %d", sum);
    }
    printf("\n");
    return 0;
}