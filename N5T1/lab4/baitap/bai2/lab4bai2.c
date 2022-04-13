#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
struct arr
{
    int n;
};

int isPrime(int num)
{
    if (num < 2)
    {
        return 0;
    }
    if (num == 2)
    {
        return 1;
    }
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
void *thr1(void *ar)
{
    struct arr *ap = (struct arr *)ar;
    for (int i = 0; i <= ap->n; i++)
    {
        if (isPrime(i))
        {
            printf("%d,\t", i);
        }
    }
    printf("\n");
}
int main(int argc, char *argv[])
{

    int n = atoi(argv[1]);
    struct arr ar;
    ar.n = n;

    pthread_t tid;

    pthread_create(&tid, NULL, thr1, (void *)&ar);
    pthread_join(tid, NULL);
    return 0;
}