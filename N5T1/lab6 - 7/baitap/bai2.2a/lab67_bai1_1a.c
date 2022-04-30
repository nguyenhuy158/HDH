#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
   char a[2] = "+", b[2] = "-", c[2] = "x", d[2] = "/";
   int result, temp, tep;
   int fp[2];
   int pid;
   if(argc<4){
      printf("Doi so thieu.\n");
      return -1;
   }
   if(pipe(fp)==0){
      pid = fork();
      if(pid<0){
      	 printf("Fork failed\n"); 
         return -1;
      }
      else if(pid==0){
         printf("Data from child: %d, %d, %s\n", atoi(argv[1]), atoi(argv[2]), argv[3]);
         if(strcmp(argv[3], a) == 0){
	 	result = atoi(argv[1]) + atoi(argv[2]);
	 	close(fp[0]);
        	write(fp[1], &result, sizeof(result));
	 }
         else if(strcmp(argv[3], b) == 0){
	 	result = atoi(argv[1]) - atoi(argv[2]);
	 	close(fp[0]);
        	write(fp[1], &result, sizeof(result));
	 }
	 else if(strcmp(argv[3], c) == 0){
	 	result = atoi(argv[1]) * atoi(argv[2]);
	 	close(fp[0]);
        	write(fp[1], &result, sizeof(result));
	 }
	 else if(strcmp(argv[3], d) == 0){
	 	result = atoi(argv[1]) / atoi(argv[2]);
	 	close(fp[0]);
        	write(fp[1], &result, sizeof(result));
	 }
	 else{
	 	printf("Doi so truyen vao khong hop le\n");
	 	return -1;
	 }
      }
      else{
         close(fp[1]);
         read(fp[0], &temp, sizeof(result));
	 printf("%d %s %d = %d\n", atoi(argv[1]), (argv[3]), atoi(argv[2]), temp);
       }
    }
   else{
	  printf("Pipe failed\n"); 
	  return -2;
   }
}

