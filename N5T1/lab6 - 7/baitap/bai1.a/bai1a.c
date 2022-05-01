#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fp[2];
	int pid, n, factorial = 1;
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

	if (pipe(fp) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			// children
			// đọc file sau đó chạy vòng lặp tính n! và ghi file
			read(fp[0], &n, sizeof(n));
			int i;
			for (i = 2; i <= n; i++)
			{
				factorial *= i;
			}
			write(fp[1], &factorial, sizeof(int));
		}
		else
		{
			// parent
			// chuyển sang int
			// ghi vào file
			// nghỉ 1s
			// đọc kết quả từ file
			// in ra màng hình
			n = atoi(argv[1]);
			write(fp[1], &n, sizeof(n));
			sleep(1);
			read(fp[0], &factorial, sizeof(int));
			printf("%d ! = %d\n", n, factorial);
		}
	}
	else
	{
		printf("pipe failed\n");
		return -2;
	}
}
