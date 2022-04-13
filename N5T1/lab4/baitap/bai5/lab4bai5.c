#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
struct arr
{
    int n;
    int a[10];
};
struct file
{
    struct arr ar;
    char *filename;
};
static int n = 0;
static long loser = 1;
static long sum = 0;
void *thr1(void *ar)
{
    struct arr *ap = (struct arr *)ar;
    if (ap->n <= 0)
    {
        printf("can nhap n > 0\n");
        return 0;
    }

    for (int i = 1; i <= ap->n; i++)
    {
        loser *= i;
    }
}
void *thr2(void *ar)
{
    struct arr *ap = (struct arr *)ar;
    for (long i = 1; i <= loser; i++)
    {
        if (i % 2 == 0)
        {
            sum += i;
        }
    }
}
void *thr3(void *ar)
{
    struct file *fi = (struct file *)ar;
    FILE *out;
    int count;
    out = fopen(fi->filename, "w");

    fprintf(out, "n = %d\n", fi->ar.n);
    fprintf(out, "%d! = %ld\n", fi->ar.n, loser);
    fprintf(out, "sum = %ld\n", sum);

    fclose(out);
}
int main(int argc, char *argv[])
{
    int i;
    pthread_t tid[3];
    struct arr ar;
    ar.n = atoi(argv[1]);

    int status, *pstatus = &status;
    pthread_create(&tid[0], NULL, thr1, (void *)&ar);
    // pthread_join(tid[0], NULL);
    if (pthread_join(tid[0], (void **)pstatus) == 0)
    {
        if (pthread_create(&tid[1], NULL, thr2, (void *)&ar) == 0)
        {
            struct file arf;
            arf.ar = ar;
            arf.filename = argv[2];
            pthread_create(&tid[2], NULL, thr3, (void *)&arf);
        }
    }

    printf("n = %d\n", ar.n);
    printf("%d! = %ld\n", ar.n, loser);
    printf("sum = %ld\n", sum);
    pthread_join(tid[2], NULL);
    return 0;
}