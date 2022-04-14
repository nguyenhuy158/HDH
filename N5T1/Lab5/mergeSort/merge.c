#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

int opt_a;
int opt_t;
int opt_r;

// number of elements in array
//#define MAX 15
//#define MAX 16
int MAX;

// number of threads
//#define THREAD_MAX 4
int THREAD_MAX;

// using namespace std;

// array of size MAX
int *a;

// thread control parameters
struct tsk
{
    int tsk_no;
    int tsk_low;
    int tsk_high;
};

// merge function for merging two parts
void merge(int low, int mid, int high)
{

    // n1 is size of left part and n2 is size of right part
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *left = malloc(n1 * sizeof(int));
    int *right = malloc(n2 * sizeof(int));

    int i;
    int j;

    // storing values in left part
    for (i = 0; i < n1; i++)
        left[i] = a[i + low];

    // storing values in right part
    for (i = 0; i < n2; i++)
        right[i] = a[i + mid + 1];

    int k = low;

    i = j = 0;

    // merge left and right in ascending order
    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }

    // insert remaining values from left
    while (i < n1)
        a[k++] = left[i++];

    // insert remaining values from right
    while (j < n2)
        a[k++] = right[j++];

    free(left);
    free(right);
}

// merge sort function
void merge_sort(int low, int high)
{

    // calculating mid point of array
    int mid = low + (high - low) / 2;

    if (low < high)
    {
        // calling first half
        merge_sort(low, mid);

        // calling second half
        merge_sort(mid + 1, high);

        // merging the two halves
        merge(low, mid, high);
    }
}

// thread function for multi-threading
void *
merge_sort123(void *arg)
{
    struct tsk *tsk = arg;
    int low;
    int high;

    // calculating low and high
    low = tsk->tsk_low;
    high = tsk->tsk_high;

    // evaluating mid point
    int mid = low + (high - low) / 2;

    if (low < high)
    {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }

    return 0;
}

// Driver Code
int main(int argc, char **argv)
{
    clock_t start, end, duration;
    start = clock();

    char *cp;
    struct tsk *tsk;

    MAX = 20;
    THREAD_MAX = 4;

    // use new/general algorithm by default
    opt_a = 1;

    // allocate the array
    a = malloc(sizeof(int) * MAX);

    // generating random values in array
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

    // creating 4 threads
    for (int i = 0; i < THREAD_MAX; i++)
    {
        tsk = &tsklist[i];
        pthread_create(&threads[i], NULL, merge_sort123, tsk);
    }

    // joining all 4 threads
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(threads[i], NULL);

    // merging the final 4 parts

    merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1);
    merge(MAX / 2, MAX / 2 + (MAX - 1 - MAX / 2) / 2, MAX - 1);
    merge(0, (MAX - 1) / 2, MAX - 1);

    // displaying sorted array
    printf("\n\nOutput:");
    for (int i = 0; i < MAX; i++)
        printf(" %d", a[i]);
    printf("\n");

    end = clock();

    duration = (end - start);

    printf("Time taken : %f seconds\n", (float)duration / CLOCKS_PER_SEC);
    return 0;
}