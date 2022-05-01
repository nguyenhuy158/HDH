#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#define SIZE 256
#define LENGTH 20

int main(int argc, char* argv[]) {
	int *shm_0, *shm_1, shmid[2], index = 0, j, result = 0, pid;
	char i;
	key_t key;
	for(i='a'; i<'c'; i++) {
		key = ftok(".", i);
		shmid[index] = shmget(key, SIZE, IPC_CREAT | 0666);
		index++;
	}
	shm_0 = (int*) shmat(shmid[0], 0, 0);
	shm_1 = (int*) shmat(shmid[1], NULL, 0);
	pid = fork();
	if(pid==0) { // child
		srand((int) time(0));
		shm_0[0] = LENGTH;
		printf("Array: ");
		for (j = 1; j < LENGTH + 1; j++) {
			shm_0[j] = rand() % 101;
			printf("%d  ", shm_0[j]);
		}
		sleep(3); 
		printf("\nSum of array's element = %d\n", shm_1[0]);
		shmdt((void*) shm_0);  
		shmdt((void*) shm_1);
		shmctl(shmid[0], IPC_RMID, (struct shmid_ds*) 0);  
		shmctl(shmid[1], IPC_RMID, (struct shmid_ds*) 0);
		return 0;
	}
	else if(pid >0) { 
		sleep(1);
		for (j = 1; j < shm_0[0] + 1; j++) {
			result += shm_0[j];
		}
		shm_1[0] = result;
		wait(NULL);
		shmdt((void*) shm_0);
		shmdt((void*) shm_1);
		shmctl(shmid[0], IPC_RMID, (struct shmid_ds*) 0);
		shmctl(shmid[1], IPC_RMID, (struct shmid_ds*) 0);
		return 0;
	}
	return 0;
}

