#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]){
	mkfifo("myfifo", 0777);
	int readfd, writefd, result, send;
	if (fork() != 0){
		readfd = open("myfifo", O_RDONLY);
		wait(NULL);		
		read(readfd, &result, sizeof(int));
		FILE*file = fopen("resultB.txt", "w");
		fprintf(file, "%s %s %s = %d", argv[1], argv[3], argv[2], result);
		fclose(file);
		close(readfd);
	}
	else{
		writefd = open("myfifo", O_WRONLY);
		if (strcmp(argv[3], "+") == 0)
			send = atoi(argv[1]) + atoi(argv[2]);
		if (strcmp(argv[3], "-") == 0)
			send = atoi(argv[1]) - atoi(argv[2]);
		if (strcmp(argv[3], "*") == 0)
			send = atoi(argv[1]) * atoi(argv[2]);
		if (strcmp(argv[3], "/") == 0)
			send = atoi(argv[1]) / atoi(argv[2]);
		write(writefd, &send, sizeof(int));
		close(writefd);
	}
	return 0;
}

