#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

struct arr
{
    int n;
    char s[1000];
};
struct file
{
    struct arr ar;
    char *filename;
};

void *thrRead(void *ar)
{
    struct file *fi = (struct file *)ar;
    FILE *in;
    int count;
    in = fopen(fi->filename, "rb");
    char ch;
    int i = 0;
    do
    {
        ch = fgetc(in);
        fi->ar.s[i++] = ch;
        // printf("%c", ch);

    } while (ch != EOF);
    fi->ar.n = i;

    // printf("\n");
    fclose(in);
}
void *thrWrite(void *ar)
{
    struct file *fi = (struct file *)ar;
    FILE *out;
    int count;
    out = fopen(fi->filename, "wb");
    for (int i = 0; i < fi->ar.n; i++)
    {
        fprintf(out, "%c", fi->ar.s[i]);
    }
    printf("Da sao chep thanh cong %d ki tu.\n", fi->ar.n);
    fclose(out);
}
int main(int argc, char *argv[])
{
    pthread_t tid[4];

    int status, *pstatus = &status;

    struct file arf;
    // arf.ar = ar;
    arf.filename = argv[1];
    pthread_create(&tid[0], NULL, thrRead, (void *)&arf);
    pthread_join(tid[0], NULL);

    // struct file arf;
    // arf.ar = ar;
    arf.filename = argv[2];
    pthread_create(&tid[1], NULL, thrWrite, (void *)&arf);
    pthread_join(tid[1], NULL);
    return 0;
}