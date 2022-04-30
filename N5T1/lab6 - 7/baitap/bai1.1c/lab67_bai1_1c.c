//lab6_7.1C.c
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
struct Message{
	int mtype;
	char* content;
};
int main(int argc, char* argv[]){
	int mid, pid;
	key_t key;
	struct Message msg;
	msg.content = (char*) malloc(BUFSIZ);
	if((key = ftok(".", 65)) == -1){
		perror("Key created.\n");
		return 1;
	}
	if(mid=msgget(key, IPC_CREAT | 0666) == -1){
		perror("Queue created.\n");
		return 2;
	}
	pid = fork();
	if(pid>0){ 
		msg.mtype = 1;
		msg.content = argv[1];
		if(atoi(argv[1]) < 3){
			printf("Doi so truyen vao khong hop le\n");
			return 0;
		}
		if(msgsnd(mid, &msg, sizeof(msg), 0) == -1){
			return 4;
		}
		sleep(3);
		if(msgrcv(mid, &msg, sizeof(msg), 2, 0) == -1){
			return 5;
		}
		int result = msg.content;
		printf("%d! = %d\n", atoi(argv[1]), result);
		return 0;
	}
	else if(pid == 0){
		sleep(1);
		if(msgrcv(mid, &msg, sizeof(msg), 1, 0) == -1){
			return 5;
		}
		int temp = 1;
		int d = atoi(msg.content);
		for(int i = 1; i<=d; i++) temp=temp*i;
		msg.content = temp;
		msg.mtype = 2;
		if(msgsnd(mid, &msg, sizeof(msg), 0) == -1) return 4;
		return 0;
	}
	else{
		perror("Fork failed."); 
		return 3; 
	}
	return 0;
}


