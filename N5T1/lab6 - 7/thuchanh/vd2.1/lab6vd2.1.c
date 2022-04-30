#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SIZE 256
int main(int argc, char *argv[])
{
    // tạo biến lưu trữ
    int *shm, shmid, k, pid;
    key_t key;
    if ((key = ftok(".", 'a')) == -1)
    {
        perror("Key created.\n");
        return 1;
    }
    // shmid lấy id từ shmget dùng để tạo SM
    if (shmid = shmget(key, SIZE, IPC_CREAT | 0666) == -1)
    {
        perror("Shared memory created.\n");
        return 2;
    }
    shm = (int *)shmat(shmid, 0, 0);
    pid = fork();
    if (pid == 0)
    { // child
        shm[0] = atoi(argv[1]);
        shm[1] = atoi(argv[2]);
        sleep(3);
        printf("%d + %d = %d\n", shm[0], shm[1], shm[2]);
        // sử dụng để gỡ SM khỏi tiến trình
        shmdt((void *)shm);
        shmctl(shmid, IPC_RMID, (struct shmid_ds *)0);
        return 0;
    }
    else if (pid > 0)
    { // parent
        sleep(1);
        shm[2] = shm[1] + shm[0];
        // sử dụng để gỡ SM khỏi tiến trình
        shmdt((void *)shm);
        sleep(5);
        return 0;
    }
    else
    {
        perror("Fork failed.");
        return 4;
    }
    return 0;
}