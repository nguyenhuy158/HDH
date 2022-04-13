// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Doi so truyen khong dung.");
    }
    else
    {
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);
        char *oper = argv[3];

        if (strcmp(oper, "+") == 0)
        {
            printf("Ket qua: %d", add(a, b));
        }
        else if (strcmp(oper, "-") == 0)
        {
            printf("Ket qua: %d", sub(a, b));
        }
        else
        {
            printf("Doi so truyen khong dung.");
        }
    }
    printf("\n");
    return 0;
}