#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

int opt_a;
int opt_t;
int opt_r;

int MAX;

int THREAD_MAX;

int *a;

struct tsk
{
    int tsk_no;
    int tsk_low;
    int tsk_high;
};

void merge(int low, int mid, int high)
{

    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *left = malloc(n1 * sizeof(int));
    int *right = malloc(n2 * sizeof(int));

    int i;
    int j;

    for (i = 0; i < n1; i++)
        left[i] = a[i + low];

    for (i = 0; i < n2; i++)
        right[i] = a[i + mid + 1];

    int k = low;

    i = j = 0;

    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }

    while (i < n1)
        a[k++] = left[i++];

    while (j < n2)
        a[k++] = right[j++];

    free(left);
    free(right);
}

void merge_sort(int low, int high)
{

    int mid = low + (high - low) / 2;

    if (low < high)
    {
        merge_sort(low, mid);

        merge_sort(mid + 1, high);

        merge(low, mid, high);
    }
}

void *
merge_sort123(void *arg)
{
    struct tsk *tsk = arg;
    int low;
    int high;

    low = tsk->tsk_low;
    high = tsk->tsk_high;

    int mid = low + (high - low) / 2;

    if (low < high)
    {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }

    return 0;
}

int main(int argc, char **argv)
{
    clock_t start, end, duration;
    start = clock();

    char *cp;
    struct tsk *tsk;

    MAX = 20;
    THREAD_MAX = 4;

    opt_a = 1;

    a = malloc(sizeof(int) * MAX);

    if (opt_t)
        printf("ORIG:");
    for (int i = 0; i < MAX; i++)
    {
        if (opt_r)
            a[i] = MAX - i;
        else
            a[i] = rand() % 100;
        if (opt_t)
            printf(" %d", a[i]);
    }
    if (opt_t)
        printf("\n");

    printf("\n\nInput:");
    for (int i = 0; i < MAX; i++)
        printf(" %d", a[i]);
    printf("\n");

    pthread_t threads[THREAD_MAX];
    struct tsk tsklist[THREAD_MAX];

    int len = MAX / THREAD_MAX;

    int low = 0;

    for (int i = 0; i < THREAD_MAX; i++, low += len)
    {
        tsk = &tsklist[i];
        tsk->tsk_no = i;

        if (opt_a)
        {
            tsk->tsk_low = low;
            tsk->tsk_high = low + len - 1;
            if (i == (THREAD_MAX - 1))
                tsk->tsk_high = MAX - 1;
        }

        else
        {
            tsk->tsk_low = i * (MAX / THREAD_MAX);
            tsk->tsk_high = (i + 1) * (MAX / THREAD_MAX) - 1;
        }

        if (opt_t)
            printf("RANGE %d: %d %d\n", i, tsk->tsk_low, tsk->tsk_high);
    }

    for (int i = 0; i < THREAD_MAX; i++)
    {
        tsk = &tsklist[i];
        pthread_create(&threads[i], NULL, merge_sort123, tsk);
    }

    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(threads[i], NULL);

    merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1);
    merge(MAX / 2, MAX / 2 + (MAX - 1 - MAX / 2) / 2, MAX - 1);
    merge(0, (MAX - 1) / 2, MAX - 1);

    printf("\n\nOutput:");
    for (int i = 0; i < MAX; i++)
        printf(" %d", a[i]);
    printf("\n");

    end = clock();

    duration = (end - start);

    printf("Time taken : %f seconds\n", (float)duration / CLOCKS_PER_SEC);
    return 0;
}