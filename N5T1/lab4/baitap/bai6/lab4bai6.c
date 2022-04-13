#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
struct arr
{
    int n;
    int a[100];
};
struct file
{
    struct arr ar;
    char *filename;
};
static int size = 0;
static int arr[100];
static int arrSorted[100];
static long sum = 0;
void *thr1(void *ar)
{
    struct file *fi = (struct file *)ar;
    FILE *in;
    int count;
    in = fopen(fi->filename, "r");

    fscanf(in, "%d", &(fi->ar.n));

    for (int i = 0; i < fi->ar.n; i++)
    {
        int temp = 0;
        fscanf(in, "%d", &temp);
        fi->ar.a[i] = temp;
    }

    fclose(in);
}
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
void *thr2(void *ar)
{
    struct arr *ap = (struct arr *)ar;
    int j = 0;
    for (int i = 0; i < ap->n; i++)
    {
        if (isPrime(ap->a[i]))
        {
            sum += ap->a[i];
            arrSorted[j] = ap->a[i];
            arr[j++] = ap->a[i];
        }
    }
    size = j;
}
void *thr3(void *ar)
{
    struct arr *ap = (struct arr *)ar;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arrSorted[i] > arrSorted[j])
            {
                int temp = arrSorted[i];
                arrSorted[i] = arrSorted[j];
                arrSorted[j] = temp;
            }
        }
    }
}
void *thr4(void *ar)
{
    struct file *fi = (struct file *)ar;
    FILE *out;
    int count;
    out = fopen(fi->filename, "w");

    fprintf(out, "So phan tu mang: %d\n", fi->ar.n);
    for (int i = 0; i < fi->ar.n; i++)
    {
        fprintf(out, "%d ", fi->ar.a[i]);
    }
    fprintf(out, "\n");

    fprintf(out, "Mang cac so nguyen to:\n");
    for (int i = 0; i < size; i++)
    {
        fprintf(out, "%d ", arr[i]);
    }

    fprintf(out, "\n");
    fprintf(out, "Tong cac so nguyen to: %ld\n", sum);

    fprintf(out, "Mang cac so nguyen to da duoc sap xep: \n");

    for (int i = 0; i < size; i++)
    {
        fprintf(out, "%d ", arrSorted[i]);
    }
    fprintf(out, "\n");
    fclose(out);
}
int main(int argc, char *argv[])
{
    int i;
    pthread_t tid[4];
    struct arr ar;
    ar.n = atoi(argv[1]);
    struct file arf;
    arf.ar = ar;
    arf.filename = argv[1];

    int status, *pstatus = &status;
    pthread_create(&tid[0], NULL, thr1, (void *)&arf);

    if (pthread_join(tid[0], (void **)pstatus) == 0)
    {

        if (pthread_create(&tid[1], NULL, thr2, (void *)&arf) == 0)
        {
            if (pthread_create(&tid[2], NULL, thr3, (void *)&arf) == 0)
            {
                arf.filename = "result.txt";
                pthread_create(&tid[3], NULL, thr4, (void *)&arf);
            }
        }
    }

    pthread_join(tid[3], NULL);
    return 0;
}