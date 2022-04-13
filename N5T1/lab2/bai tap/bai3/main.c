// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int size = 0;
    for (int i = 1; i < argc; i++)
    {
        // printf("%s \t", argv[i]);
        if (atoi(argv[i]) != 0 || strcmp(argv[i], "0") == 0)
        {
            size++;
        }
    }

    int a[size];
    int index = 0;
    for (int i = 1; i < argc; i++)
    {
        if (atoi(argv[i]) != 0 || strcmp(argv[i], "0") == 0)
        {
            a[index++] = atoi(argv[i]);
        }
    }

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (a[i] > a[j])
            {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    printf("Day tang la ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n");
    return 0;
}