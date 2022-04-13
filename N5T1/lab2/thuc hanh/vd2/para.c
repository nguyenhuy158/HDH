// para.c
#include <stdio.h>

int main(int argc, char **argv)
{
    printf("Number of arguments: %i \n", argc);
    int i = 0;
    for (i = 0; i < argc; i++)
        printf("Argument[%i] %s\t", i, argv[i]);
    printf("\n");
    return 0;
}