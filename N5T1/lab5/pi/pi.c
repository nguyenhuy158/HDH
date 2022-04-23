#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static int counter = 0;
static int m;
void *thr(void *ar)
{
    FILE *out_file = fopen("m_point.txt", "a");
    int max = 2;
    int min = -1;
    for (int index = 0; index < m; index++)
    {
        float x = (((float)rand() / (float)(RAND_MAX)) * max) + min;
        float y = (((float)rand() / (float)(RAND_MAX)) * max) + min;

        fprintf(out_file, "(%2.2f, %2.2f)\n", x, y);

        float d = sqrt(x * x + y * y);
        if (d <= 1.0)
        {
            counter += 1;
        }
    }
}

int main(int argc, char *argv[])
{
    int i;
    int status, *pstatus = &status;

    int n = atoi(argv[1]);
    m = atoi(argv[2]);

    pthread_t tid[n];

    for (i = 0; i < n; i++)
    {
        // printf("%d\n", i);
        // if (i != 0)
        // {
        //     if (pthread_join(tid[i - 1], (void **)pstatus) == 0)
        //     {
        //         pthread_create(&tid[i], NULL, thr, (void *)&tid[i]);
        //     }
        // }
        // else
        // {
        //     pthread_create(&tid[i], NULL, thr, (void *)&tid[i]);
        // }
        pthread_create(&tid[i], NULL, thr, (void *)&tid[i]);
        sleep(1);
    }

    printf("%d\n", counter);
    printf("pi = %.6f\n", 4.0 * counter / (n * m));

    return 0;
}
