#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
// my include
#include <sys/wait.h>

#define FIFO1 "/tmp/ff.1"
#define FIFO2 "/tmp/ff.2"
#define PM 0666
extern int errno;
#define PIPE_BUF 4096
int main(int argc, char *argv[])
{
    char s1[PIPE_BUF], s2[PIPE_BUF];
    int childpid, readfd, writefd;
    if ((mknod(FIFO1, S_IFIFO | PM, 0) < 0) && (errno != EEXIST))
    {
        printf("Fail to create FIFO 1. Aborted.\n");
        return -1;
    }
    if ((mknod(FIFO2, S_IFIFO | PM, 0) < 0) && (errno != EEXIST))
    {
        unlink(FIFO1);
        printf("Fail to create FIFO 2. Aborted.\n");
        return -1;
    }
    childpid = fork(); // tạo tiến trình
    if (childpid == 0)
    { // child
        if ((readfd = open(FIFO1, 0)) < 0)
            perror("Child cannot open readFIFO.\n");
        if ((writefd = open(FIFO2, 1)) < 0)
            perror("Child cannot open writeFIFO.\n");
        // đọc dữ liệu từ s2
        // in ra màng hình
        // nhập dữ liệu từ bàn phím
        // ghi vào s1
        read(readfd, s2, PIPE_BUF);
        printf("Child read from parent: %s\n", s2);
        printf("Enter response: ");
        gets(s1);
        write(writefd, s1, strlen(s1));
        close(readfd);
        close(writefd);
        return 1;
    }
    else if (childpid > 0)
    { // parent
        if ((writefd = open(FIFO1, 1)) < 0)
            perror("Parent cannot open writeFIFO.\n");
        if ((readfd = open(FIFO2, 0)) < 0)
            perror("Child cannot open readFIFO.\n");

        // nhận dữ liệu từ bàn phím
        // ghi vào s1 của mình
        // in ra màng hình
        // đợi tiến trình con hoàn thành
        printf("Enter data to FIFO1: ");
        gets(s1);
        write(writefd, s1, strlen(s1));
        read(readfd, , PIPE_BUF);
        printf("Parent read from child: %s\n", s2);
        while (wait((int *)0) != childpid)
            ;
        close(readfd);
        close(writefd);
        if (unlink(FIFO1) < 0)
            perror("Cannot remove FIFO1.\n");
        if (unlink(FIFO2) < 0)
            perror("Cannot remove FIFO2.\n");
        return 1;
    }
    else
    {
        printf("Fork failed\n");
        return -1;
    }
}