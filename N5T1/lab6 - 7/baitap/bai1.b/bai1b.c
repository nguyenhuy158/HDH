#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <fcntl.h>

#define FIFO1 "/tmp/ff.1"
#define FIFO2 "/tmp/ff.2"
#define PM 0666
extern int errno;
int main(int argc, char *argv[])
{
   int s1, s2;
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
   // thiếu dữ liệu đầu vào
   if (argc < 2)
   {
      printf("Doi so thieu\n");
      return -1;
   }
   // nhập dữ liệu sai
   else if (atoi(argv[1]) <= 3)
   {
      printf("Nhap sai\n");
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
      read(readfd, &s2, sizeof(s2));
      printf("Child read from parent: %d\n", s2);
      // tính giai thừa sau đó ghi lại vào file
      int sum = 1;
      for (int i = 2; i <= s2; i++)
      {
         sum *= i;
      }
      s1 = sum;
      write(writefd, &s1, sizeof(s1));
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
      s1 = atoi(argv[1]);
      write(writefd, &s1, sizeof(s1));
      read(readfd, &s2, sizeof(s2));

      printf("%d! = %d\n", s1, s2);
      // while (wait((int *)0) != childpid)
      //    ;
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