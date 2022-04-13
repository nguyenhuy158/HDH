#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void *thr1(void *ar)
{
    printf("This is thread % d\n", *((int *)ar));
    sleep(2);
}
int main(int argc, char *argv[])
{
    int i;
    int num = atoi(argv[1]);
    pthread_t tid[num];
    for (i = 0; i < num; i++)
    {
        pthread_create(&tid[i], NULL, thr1, (void *)&tid[i]);
    }
    sleep(10);
    return (0);
}