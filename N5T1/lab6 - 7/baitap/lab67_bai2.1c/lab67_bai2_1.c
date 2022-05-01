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
int main(int argc, char* argv[])
{
	int mid, id, pid;
	key_t key;
	struct Message msg1, msg2, msg3, msg4;
	if((key = ftok(".", 'a'))==-1){
		perror("Key created.\n");
		return 1;
	}
	if(mid=msgget(key, IPC_CREAT | 0666)==-1){
		perror("Queue created.\n");
		return 2;
	}
	pid = fork();
	if(pid>0) { 
		msg1.mtype=1;
		msg2.mtype=1;
		msg3.mtype=1;
		msg1.content=atoi(argv[1]);
		msg2.content=atoi(argv[2]);
		msg3.content=(argv[3]);
		if(msgsnd(mid, &msg1, sizeof(msg1), 0)==-1){
			return 4;
		}
		if(msgsnd(mid, &msg2, sizeof(msg2), 0)==-1){
			return 4;
		}
		if(msgsnd(mid, &msg3, sizeof(msg3), 0)==-1){
			return 4;
		}
		sleep(5);
		if(msgrcv(mid, &msg4, sizeof(msg4), 1, 0)==-1){
			return 5;
		}
		int p= msg4.content;
		FILE* fl;
		fl=fopen("ketqua.txt","w");
		if(fl==NULL){
			printf("Khong the ghi file\n");
			return 0;
		}
		fprintf(fl,"%d %s %d = %d", msg1.content, msg3.content, msg2.content, p);
		return 0;
	}
	else if(pid ==0) { 
		sleep(1);
		if(msgrcv(mid, &msg1, sizeof(msg1), 1, 0)==-1){
			return 5;
		}
		if(msgrcv(mid, &msg2, sizeof(msg2), 1, 0)==-1){
			return 5;
		}
		if(msgrcv(mid, &msg3, sizeof(msg3), 1, 0)==-1){
			return 5;
		}
		msg4.mtype=1;
		int o=0;
		int a=msg1.content;
		int b=msg2.content;
		if ( strcmp(msg3.content, "+") == 0) {
                o=a+b;
            } else if ( strcmp(msg3.content, "-") == 0 ) {
                o=a-b;
            } else if ( strcmp(msg3.content, "*") == 0 ) {
                o=a*b;
            } else {
                 o=a/b;
            }
		msg4.content=o;
		if(msgsnd(mid, &msg4, sizeof(msg4), 0)==-1){
			return 4;
		}
		return 0;
	}
	else { perror("Fork failed."); return 3; }
	return 0;
}
