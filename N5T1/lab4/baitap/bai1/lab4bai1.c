#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
struct arr
{
    int n;
    int a[20];
};

static float avg = 0;
static int max = 0;
static int min = 0;
void *thr1(void *ar)
{
    struct arr *ap = (struct arr *)ar;
    int i = 0;
    float sum = 0;
    for (i = 0; i < ap->n; i++)
    {
        sum += ap->a[i];
    }
    avg = sum / ap->n;
}
void *thr2(void *ar)
{
    struct arr *ap = (struct arr *)ar;
    int i = 0;
    max = ap->a[0];
    for (i = 1; i < ap->n; i++)
    {
        if (max < ap->a[i])
        {
            max = ap->a[i];
        }
    }
}
void *thr3(void *ar)
{
    struct arr *ap = (struct arr *)ar;
    int i = 0;
    min = ap->a[0];
    for (i = 1; i < ap->n; i++)
    {
        if (min > ap->a[i])
        {
            min = ap->a[i];
        }
    }
}
int main(int argc, char *argv[])
{
    int i;
    pthread_t tid[3];
    struct arr ar;
    ar.n = argc - 1;
    for (int i = 0; i < argc - 1; i++)
    {
        ar.a[i] = atoi(argv[i + 1]);
    }

    int status, *pstatus = &status;
    pthread_create(&tid[0], NULL, thr1, (void *)&ar);
    pthread_join(tid[0], NULL);
    pthread_create(&tid[1], NULL, thr2, (void *)&ar);
    pthread_join(tid[1], NULL);
    pthread_create(&tid[2], NULL, thr3, (void *)&ar);
    pthread_join(tid[2], NULL);

    printf("so lon nhat: %d\n", max);
    printf("so nho nhat: %d\n", min);
    printf("trung binh: %.2f\n", avg);
    return 0;
}