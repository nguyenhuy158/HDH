#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/wait.h>

#define FIFO1 "/tmp/ff.1"

#define PM 0666
extern int errno;


int main(int argc, char* argv[])
{
   int childpid, readfd, writefd, result, temp, sum = 1, i;
   if((mknod(FIFO1, S_IFIFO | PM, 0)<0)&&(errno!=EEXIST)){
      unlink(FIFO1);
      printf("Fail to create FIFO 1. Aborted.\n");
      return -1;
   }
   if(argc < 2 || argc > 2) {
	printf("Doi so truyen vao khong dung\n");
	return -1;	
   }
   if(atoi(argv[1]) < 3) return -1;
   
   childpid=fork();
   if(childpid==0){   //child
      if((writefd=open(FIFO1, 1))<0)
         perror("Child cannot open writeFIFO.\n");
      printf("Du lieu tien trinh con nhan duoc: %d\n",atoi(argv[1]));
      for(i=1;i<=atoi(argv[1]);i++) sum=sum*i;
      result = sum;
      write(writefd, &result, sizeof(atoi(argv[1])));
      close(writefd);
      return -2;
   }
   else if(childpid>0) {   //parent
      if((readfd=open(FIFO1, 0))<0)
         perror("Parent cannot open readFIFO.\n");
      read(readfd, &temp, sizeof(atoi(argv[1])));
      printf("%d! = %d\n", atoi(argv[1]), temp);
      close(readfd);
      if(unlink(FIFO1)<0)
         perror("Cannot remove FIFO1.\n");
      return -2;
   }
   else { printf("Fork failed\n"); return -1;
}
}

